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
import androidx.annotation.Keep;
import androidx.core.app.ActivityCompat;
import android.util.Log;
import android.util.DisplayMetrics;
import android.view.*;
import android.content.pm.PackageManager;

public class GameActivity extends SDLActivity {
    private static DisplayMetrics metrics = new DisplayMetrics();
    private static String gamePath = "";
    private static Context context;
    private static Vibrator vibrator = null;
    protected final int[] externalStorageRequestDummy = new int[1];
    public static final int EXTERNAL_STORAGE_REQUEST_CODE = 1;
    private static boolean immersiveActive = false;
    private static boolean mustCacheArchive = false;
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
    protected void onCreate(Bundle savedInstanceState) {
        Log.d("GameActivity", "started");

        context = this.getApplicationContext();

        String permission = "android.permission.VIBRATE";
        int res = context.checkCallingOrSelfPermission(permission);
        if (res == PackageManager.PERMISSION_GRANTED) {
            vibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
        } else {
            Log.d("GameActivity", "Vibration disabled: could not get vibration permission.");
        }

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
        handleIntent(intent);
        resetNative();
        startNative();
    }

    protected void handleIntent(Intent intent) {
        Uri game = intent.getData();

        if (game != null) {
            // If we have a game via the intent data we we try to figure out how we have to load it. We
            // support the following variations:
            // * a main.lua file: set gamePath to the directory containing main.lua
            // * otherwise: set gamePath to the file
            if (game.getScheme().equals("file")) {
                Log.d("GameActivity", "Received intent with path: " + game.getPath());
                // If we were given the path of a main.lua then use its
                // directory. Otherwise use full path.
                List<String> path_segments = game.getPathSegments();
                if (path_segments.get(path_segments.size() - 1).equals("main.lua")) {
                    gamePath = game.getPath().substring(0, game.getPath().length() - "main.lua".length());
                } else {
                    gamePath = game.getPath();
                }
            // FIXME: Add support for "content://" URI, which is mandatory in Android Nougat
            // as using "file://" protocol in that (and later) version is forbidden!
            } else {
                Log.e("GameActivity", "Unsupported scheme: '" + game.getScheme() + "'.");

                AlertDialog.Builder alert_dialog = new AlertDialog.Builder(this);
                alert_dialog.setMessage("Could not load LÖVE game '" + game.getPath()
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
            // No game specified via the intent data -> check whether we have a game.love in our assets.
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
                if (mustCacheArchive && copyAssetFile("game.love", destination_file))
                    gamePath = destination_file;
                else
                    gamePath = "game.love";
            }
        }

        Log.d("GameActivity", "new gamePath: " + gamePath);
    }

    protected void checkLovegameFolder() {
        // If no game.love was found fall back to the game in <external storage>/lovegame
        if (hasExternalStoragePermission()) {
            File ext = Environment.getExternalStorageDirectory();
            if ((new File(ext, "/lovegame/main.lua")).exists()) {
                gamePath = ext.getPath() + "/lovegame/";
            }
        } else {
            Log.d("GameActivity", "Cannot load game from external storage: permission not granted");
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
                            getWindow().getDecorView().setSystemUiVisibility(
                                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                                            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                                            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                                            | View.SYSTEM_UI_FLAG_FULLSCREEN
                                            | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
                        } else {
                            getWindow().getDecorView().setSystemUiVisibility(
                                    View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                                            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                            );
                        }

                        lock.notify();
                    }
                }
            });
        }
        ;
    }

    public boolean getImmersiveMode() {
        return immersiveActive;
    }

    public static String getGamePath() {
        GameActivity self = (GameActivity) mSingleton; // use SDL provided one
        Log.d("GameActivity", "called getGamePath(), game path = " + gamePath);

        if (gamePath.length() > 0) {
            if(self.hasExternalStoragePermission()) {
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

    public static void vibrate(double seconds) {
        if (vibrator != null) {
            vibrator.vibrate((long) (seconds * 1000.));
        }
    }

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
    boolean copyAssetFile(String fileName, String destinationFileName) {
        boolean success = false;

        // open source and destination streams
        InputStream source_stream = null;
        try {
            source_stream = getAssets().open(fileName);
        } catch (IOException e) {
            Log.d("GameActivity", "Could not open game.love from assets: " + e.getMessage());
        }

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

        Log.d("GameActivity", "Successfully copied " + fileName
                + " to " + destinationFileName
                + " (" + bytes_written + " bytes written).");
        return success;
    }

    @Keep
    public boolean hasBackgroundMusic() {
        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        return audioManager.isMusicActive();
    }

    public void showExternalStoragePermissionMissingDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(mSingleton);

        builder.setTitle ("Storage Permission Missing")
                .setMessage("LÖVE for Android will not be able to run non-packaged games without storage permission.");

        builder.setNeutralButton("Continue", null);

        AlertDialog dialog = builder.create();
        dialog.show();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (grantResults.length > 0) {
            Log.d("GameActivity", "Received a request permission result");

            if (requestCode == EXTERNAL_STORAGE_REQUEST_CODE) {
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Log.d("GameActivity", "Permission granted");
                } else {
                    Log.d("GameActivity", "Did not get permission.");
                    if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                        showExternalStoragePermissionMissingDialog();
                    }
                }

                Log.d("GameActivity", "Unlocking LÖVE thread");
                synchronized (externalStorageRequestDummy) {
                    externalStorageRequestDummy[0] = grantResults[0];
                    externalStorageRequestDummy.notify();
                }
           }
        }
    }

    @Keep
    public boolean hasExternalStoragePermission() {
        if (ActivityCompat.checkSelfPermission(this,
                Manifest.permission.WRITE_EXTERNAL_STORAGE)
                == PackageManager.PERMISSION_GRANTED) {
            return true;
        }

        Log.d("GameActivity", "Requesting permission and locking LÖVE thread until we have an answer.");
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, EXTERNAL_STORAGE_REQUEST_CODE);

        synchronized (externalStorageRequestDummy) {
            try {
                externalStorageRequestDummy.wait();
            } catch (InterruptedException e) {
                Log.d("GameActivity", "requesting external storage permission", e);
                return false;
            }
        }

        return ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED;
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
