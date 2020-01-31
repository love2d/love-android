package org.love2d.android;

import org.libsdl.app.SDLActivity;

import java.util.Arrays;
import java.util.List;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.Manifest;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Vibrator;
import android.util.Log;
import android.util.DisplayMetrics;
import android.view.*;
import android.content.pm.PackageManager;

import androidx.annotation.Keep;
import androidx.core.app.ActivityCompat;

public class GameActivity extends SDLActivity {
    private static DisplayMetrics metrics = new DisplayMetrics();
    private static String gamePath = "";
    private static Context context;
    private static Vibrator vibrator = null;
    protected final int[] externalStorageRequestDummy = new int[1];
    protected final int[] recordAudioRequestDummy = new int[1];
    public static final int EXTERNAL_STORAGE_REQUEST_CODE = 1;
    public static final int RECORD_AUDIO_REQUEST_CODE = 2;
    private static boolean immersiveActive = false;
    private static boolean mustCacheArchive = false;
    private boolean storagePermissionUnnecessary = false;
    public boolean embed = false;
    public int safeAreaTop = 0;
    public int safeAreaLeft = 0;
    public int safeAreaBottom = 0;
    public int safeAreaRight = 0;

    @Override
    protected String[] getLibraries() {
        return new String[]{
            "c++_shared",
            "mpg123",
            "openal",
            "hidapi",
            "love",
        };
    }

    @Override
    protected String getMainSharedObject() {
        String[] libs = getLibraries();
        String libname = "lib" + libs[libs.length - 1] + ".so";

        // Since Lollipop, you can simply pass "libname.so" to dlopen
        // and it will resolve correct paths and load correct library.
        // This is mandatory for extractNativeLibs=false support in
        // Marshmallow.
        if (android.os.Build.VERSION.SDK_INT >= 21) {
            return libname;
        } else {
            return getContext().getApplicationInfo().nativeLibraryDir + "/" + libname;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d("GameActivity", "started");

        context = this.getApplicationContext();

        int res = context.checkCallingOrSelfPermission(Manifest.permission.VIBRATE);
        if (res == PackageManager.PERMISSION_GRANTED) {
            vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
        } else {
            Log.d("GameActivity", "Vibration disabled: could not get vibration permission.");
        }

        // These 2 variables must be reset or it will use the existing value.
        gamePath = "";
        storagePermissionUnnecessary = false;
        embed = context.getResources().getBoolean(R.bool.embed);

        handleIntent(this.getIntent());

        super.onCreate(savedInstanceState);
        getWindowManager().getDefaultDisplay().getMetrics(metrics);

        if (android.os.Build.VERSION.SDK_INT >= 28) {
            getWindow().getAttributes().layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }
    }

    @Override
    protected void onNewIntent(Intent intent) {
        Log.d("GameActivity", "onNewIntent() with " + intent);
        if (!embed) {
            handleIntent(intent);
            resetNative();
            startNative();
        }
    }

    protected void handleIntent(Intent intent) {
        Uri game = intent.getData();

        if (!embed && game != null) {
            String scheme = game.getScheme();
            String path = game.getPath();
            // If we have a game via the intent data we we try to figure out how we have to load it. We
            // support the following variations:
            // * a main.lua file: set gamePath to the directory containing main.lua
            // * otherwise: set gamePath to the file
            if (scheme.equals("file")) {
                Log.d("GameActivity", "Received file:// intent with path: " + path);
                // If we were given the path of a main.lua then use its
                // directory. Otherwise use full path.
                List<String> path_segments = game.getPathSegments();
                if (path_segments.get(path_segments.size() - 1).equals("main.lua")) {
                    gamePath = path.substring(0, path.length() - "main.lua".length());
                } else {
                    gamePath = path;
                }
            } else if (scheme.equals("content")) {
                Log.d("GameActivity", "Received content:// intent with path: " + path);
                try {
                    String filename = "game.love";
                    String[] pathSegments = path.split("/");
                    if (pathSegments != null && pathSegments.length > 0) {
                        filename = pathSegments[pathSegments.length - 1];
                    }

                    String destination_file = this.getCacheDir().getPath() + "/" + filename;
                    InputStream data = getContentResolver().openInputStream(game);

                    // copyAssetFile automatically closes the InputStream
                    if (copyAssetFile(data, destination_file)) {
                        gamePath = destination_file;
                        storagePermissionUnnecessary = true;
                    }
                } catch (Exception e) {
                    Log.d("GameActivity", "could not read content uri " + game.toString() + ": " + e.getMessage());
                }
            } else {
                Log.e("GameActivity", "Unsupported scheme: '" + game.getScheme() + "'.");

                AlertDialog.Builder alert_dialog = new AlertDialog.Builder(this);
                alert_dialog.setMessage("Could not load LÖVE game '" + path
                        + "' as it uses unsupported scheme '" + game.getScheme()
                        + "'. Please contact the developer.");
                alert_dialog.setTitle("LÖVE for Android Error");
                alert_dialog.setPositiveButton("Exit",
                        new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {
                                finish();
                            }
                        });
                alert_dialog.setCancelable(false);
                alert_dialog.create().show();
            }
        } else {
            // No game specified via the intent data or embed build is used.
            // Check whether we have a game.love in our assets.
            boolean game_love_in_assets = false;
            try {
                List<String> assets = Arrays.asList(getAssets().list(""));
                game_love_in_assets = assets.contains("game.love");
            } catch (Exception e) {
                Log.d("GameActivity", "could not list application assets:" + e.getMessage());
            }

            if (game_love_in_assets) {
                // If we have a game.love in our assets folder copy it to the cache folder
                // so that we can load it from native LÖVE code
                String destination_file = this.getCacheDir().getPath() + "/game.love";
                
                try {
                    InputStream gameStream = getAssets().open("game.love");
                    if (mustCacheArchive && copyAssetFile(gameStream, destination_file))
                        gamePath = destination_file;
                    else
                        gamePath = "game.love";
                    storagePermissionUnnecessary = true;
                } catch (IOException e) {
                    Log.d("GameActivity", "Could not open game.love from assets: " + e.getMessage());
                    gamePath = "";
                    storagePermissionUnnecessary = false;
                }
            } else {
                gamePath = "";
                storagePermissionUnnecessary = false;
            }
        }

        Log.d("GameActivity", "new gamePath: " + gamePath);
    }

    protected void checkLovegameFolder() {
        // If no game.love was found fall back to the game in <external storage>/lovegame
        // if using normal or playstore build
        if (!embed) {
            Log.d("GameActivity", "fallback to lovegame folder");
            if (hasExternalStoragePermission()) {
                File ext = Environment.getExternalStorageDirectory();
                if ((new File(ext, "/lovegame/main.lua")).exists()) {
                    gamePath = ext.getPath() + "/lovegame/";
                }
            } else {
                Log.d("GameActivity", "Cannot load game from /sdcard/lovegame: permission not granted");
            }
        }
    }

    @Override
    protected void onDestroy() {
        if (vibrator != null) {
            Log.d("GameActivity", "Cancelling vibration");
            vibrator.cancel();
        }
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        if (vibrator != null) {
            Log.d("GameActivity", "Cancelling vibration");
            vibrator.cancel();
        }
        super.onPause();
    }

    @Override
    public void onResume() {
        super.onResume();

        if (immersiveActive) {
            int flags = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;

            if (android.os.Build.VERSION.SDK_INT >= 16) {
                flags |= View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
                         View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
                         View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
                         View.SYSTEM_UI_FLAG_FULLSCREEN;
            }
            if (android.os.Build.VERSION.SDK_INT >= 19) {
                flags |= View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
            }

            getWindow().getDecorView().setSystemUiVisibility(flags);
        }
    }

    @Keep
    public void setImmersiveMode(boolean immersive_mode) {
        if (android.os.Build.VERSION.SDK_INT < 11) {
            // The API getWindow().getDecorView().setSystemUiVisibility() was
            // added in Android 11 (a.k.a. Honeycomb, a.k.a. 3.0.x). If we run
            // on this we do nothing.
            return;
        }

        immersiveActive = immersive_mode;

        final Object lock = new Object();
        final boolean immersive_enabled = immersive_mode;
        synchronized (lock) {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    synchronized (lock) {
                        if (immersive_enabled) {
                            int flags = View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;

                            if (android.os.Build.VERSION.SDK_INT >= 16) {
                                flags |= View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
                                         View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION |
                                         View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN |
                                         View.SYSTEM_UI_FLAG_FULLSCREEN;
                            }
                            if (android.os.Build.VERSION.SDK_INT >= 19) {
                                flags |= View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
                            }
                            getWindow().getDecorView().setSystemUiVisibility(flags);
                        } else if (android.os.Build.VERSION.SDK_INT >= 16) {
                            getWindow().getDecorView().setSystemUiVisibility(
                                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE |
                                    View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                            );
                        }

                        lock.notify();
                    }
                }
            });
        }
        ;
    }

    @Keep
    public boolean getImmersiveMode() {
        return immersiveActive;
    }

    @Keep
    public static String getGamePath() {
        GameActivity self = (GameActivity) mSingleton; // use SDL provided one
        Log.d("GameActivity", "called getGamePath(), game path = " + gamePath);

        if (gamePath.length() > 0) {
            if(self.storagePermissionUnnecessary || self.hasExternalStoragePermission()) {
                return gamePath;
            } else {
                Log.d("GameActivity", "cannot open game " + gamePath + ": no external storage permission given!");
            }

        } else {
            self.checkLovegameFolder();
            if (gamePath.length() > 0)
                return gamePath;
        }

        return "";
    }

    public static DisplayMetrics getMetrics() {
        return metrics;
    }

    @Keep
    public static void vibrate(double seconds) {
        if (vibrator != null) {
            vibrator.vibrate((long) (seconds * 1000.));
        }
    }

    @Keep
    public static boolean openURL(String url) {
        Log.d("GameActivity", "opening url = " + url);
        try {
            Intent i = new Intent(Intent.ACTION_VIEW);
            i.setData(Uri.parse(url));
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_GRANT_READ_URI_PERMISSION);
            context.startActivity(i);
            return true;
        } catch (RuntimeException e) {
            Log.d("GameActivity", "love.system.openURL", e);
            return false;
        }
    }

    /**
     * Copies a given file from the assets folder to the destination.
     *
     * @return true if successful
     */
    boolean copyAssetFile(InputStream source_stream, String destinationFileName) {
        boolean success = false;

        BufferedOutputStream destination_stream = null;
        try {
            destination_stream = new BufferedOutputStream(new FileOutputStream(destinationFileName, false));
        } catch (IOException e) {
            Log.d("GameActivity", "Could not open destination file: " + e.getMessage());
        }

        // perform the copying
        int chunk_read = 0;
        int bytes_written = 0;

        assert (source_stream != null && destination_stream != null);

        try {
            byte[] buf = new byte[1024];
            chunk_read = source_stream.read(buf);
            do {
                destination_stream.write(buf, 0, chunk_read);
                bytes_written += chunk_read;
                chunk_read = source_stream.read(buf);
            } while (chunk_read != -1);
        } catch (IOException e) {
            Log.d("GameActivity", "Copying failed:" + e.getMessage());
        }

        // close streams
        try {
            if (source_stream != null) source_stream.close();
            if (destination_stream != null) destination_stream.close();
            success = true;
        } catch (IOException e) {
            Log.d("GameActivity", "Copying failed: " + e.getMessage());
        }

        Log.d("GameActivity", "Successfully copied stream to " + destinationFileName + " (" + bytes_written + " bytes written).");
        return success;
    }

    @Keep
    public boolean hasBackgroundMusic() {
        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        return audioManager.isMusicActive();
    }

    @Keep
    public void showRecordingAudioPermissionMissingDialog() {
        Log.d("GameActivity", "showRecordingAudioPermissionMissingDialog()");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                AlertDialog dialog = new AlertDialog.Builder(mSingleton)
                    .setTitle("Audio Recording Permission Missing")
                    .setMessage("It appears that this game uses mic capabilities. The game may not work correctly without mic permission!")
                    .setNeutralButton("Continue", new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface di, int id) {
                            synchronized (recordAudioRequestDummy) {
                                recordAudioRequestDummy.notify();
                            }
                        }
                    })
                    .create();
                dialog.show();
            }
        });

        synchronized (recordAudioRequestDummy) {
            try {
                recordAudioRequestDummy.wait();
            } catch (InterruptedException e) {
                Log.d("GameActivity", "mic permission dialog", e);
            }
        }
    }

    public void showExternalStoragePermissionMissingDialog() {
        AlertDialog dialog = new AlertDialog.Builder(mSingleton)
            .setTitle("Storage Permission Missing")
            .setMessage("LÖVE for Android will not be able to run non-packaged games without storage permission.")
            .setNeutralButton("Continue", null)
            .create();
        dialog.show();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (grantResults.length > 0) {
            Log.d("GameActivity", "Received a request permission result");

            switch (requestCode) {
                case EXTERNAL_STORAGE_REQUEST_CODE: {
                    if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                        Log.d("GameActivity", "Permission granted");
                    } else {
                        Log.d("GameActivity", "Did not get permission.");
                        if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.READ_EXTERNAL_STORAGE)) {
                            showExternalStoragePermissionMissingDialog();
                        }
                    }

                    Log.d("GameActivity", "Unlocking LÖVE thread");
                    synchronized (externalStorageRequestDummy) {
                        externalStorageRequestDummy[0] = grantResults[0];
                        externalStorageRequestDummy.notify();
                    }
                    break;
                }
                case RECORD_AUDIO_REQUEST_CODE: {
                    if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                        Log.d("GameActivity", "Mic ermission granted");
                    } else {
                        Log.d("GameActivity", "Did not get mic permission.");
                    }

                    Log.d("GameActivity", "Unlocking LÖVE thread");
                    synchronized (recordAudioRequestDummy) {
                        recordAudioRequestDummy[0] = grantResults[0];
                        recordAudioRequestDummy.notify();
                    }
                    break;
                }
            }
        }
    }

    @Keep
    public boolean hasExternalStoragePermission() {
        if (ActivityCompat.checkSelfPermission(this,
                Manifest.permission.READ_EXTERNAL_STORAGE)
                == PackageManager.PERMISSION_GRANTED) {
            return true;
        }

        Log.d("GameActivity", "Requesting permission and locking LÖVE thread until we have an answer.");
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, EXTERNAL_STORAGE_REQUEST_CODE);

        synchronized (externalStorageRequestDummy) {
            try {
                externalStorageRequestDummy.wait();
            } catch (InterruptedException e) {
                Log.d("GameActivity", "requesting external storage permission", e);
                return false;
            }
        }

        return ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED;
    }

    @Keep
    public boolean hasRecordAudioPermission() {
        return ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_GRANTED;
    }

    @Keep
    public void requestRecordAudioPermission() {
        if (ActivityCompat.checkSelfPermission(this,
                Manifest.permission.RECORD_AUDIO)
                == PackageManager.PERMISSION_GRANTED) {
            return;
        }

        Log.d("GameActivity", "Requesting mic permission and locking LÖVE thread until we have an answer.");
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.RECORD_AUDIO}, RECORD_AUDIO_REQUEST_CODE);

        synchronized (recordAudioRequestDummy) {
            try {
                recordAudioRequestDummy.wait();
            } catch (InterruptedException e) {
                Log.d("GameActivity", "requesting mic permission", e);
            }
        }
    }

    @Keep
    public boolean initializeSafeArea() {
        if (android.os.Build.VERSION.SDK_INT >= 28) {
            DisplayCutout cutout = getWindow().getDecorView().getRootWindowInsets().getDisplayCutout();

            if (cutout != null) {
                safeAreaTop = cutout.getSafeInsetTop();
                safeAreaLeft = cutout.getSafeInsetLeft();
                safeAreaBottom = cutout.getSafeInsetBottom();
                safeAreaRight = cutout.getSafeInsetRight();
                return true;
            }
        }

        return false;
    }
}
