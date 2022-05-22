/*
 * Copyright (c) 2006-2022 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

package org.love2d.android;

import androidx.annotation.Keep;

import org.libsdl.app.SDLActivity;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.graphics.Rect;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.os.VibrationEffect;
import android.os.Vibrator;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.DisplayCutout;
import android.view.WindowManager;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GameActivity extends SDLActivity {
    private static final String TAG = "GameActivity";

    protected Vibrator vibrator;
    protected boolean shortEdgesMode;
    private GameInfo currentGameInfo;
    private int delayedFd = -1;

    private static native void nativeSetDefaultStreamValues(int sampleRate, int framesPerBurst);

    @Override
    protected String getMainSharedObject() {
        String[] libs = getLibraries();
        // Since Lollipop, you can simply pass "libname.so" to dlopen
        // and it will resolve correct paths and load correct library.
        // This is mandatory for extractNativeLibs=false support in
        // Marshmallow.
        return "lib" + libs[libs.length - 1] + ".so";
    }

    @Override
    protected String[] getLibraries() {
        return new String[] {
            "c++_shared",
            "SDL2",
            "openal",
            "luajit",
            "love",
        };
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d(TAG, "started");

        if (checkCallingOrSelfPermission(Manifest.permission.VIBRATE) == PackageManager.PERMISSION_GRANTED) {
            vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        }

        currentGameInfo = new GameInfo();
        Intent intent = getIntent();

        super.onCreate(savedInstanceState);
        handleIntent(intent);

        // Set low-latency audio values
        nativeSetDefaultStreamValues(getAudioFreq(), getAudioSMP());

        if (android.os.Build.VERSION.SDK_INT >= 28) {
            WindowManager.LayoutParams attr = getWindow().getAttributes();
            attr.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_NEVER;
            shortEdgesMode = false;
        }

        if (delayedFd != -1) {
            // This delayed fd is only sent if an embedded game is present.
            sendFileDescriptorAsDroppedFile(delayedFd);
            delayedFd = -1;
        }
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        handleIntent(intent);
    }

    @Override
    protected void onDestroy() {
        if (vibrator != null) {
            Log.d(TAG, "Cancelling vibration");
            vibrator.cancel();
        }
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        if (vibrator != null) {
            Log.d(TAG, "Cancelling vibration");
            vibrator.cancel();
        }
        super.onPause();
    }

    @Keep
    public static DisplayMetrics getDisplayMetrics() {
        return getDisplayDPI();
    }

    @Keep
    public boolean hasEmbeddedGame() {
        AssetManager am = getAssets();
        InputStream inputStream;

        try {
            // Prioritize main.lua in assets folder
            inputStream = am.open("main.lua");
        } catch (IOException e) {
            // Not found, try game.love in assets folder
            try {
                inputStream = am.open("game.love");
            } catch (IOException e2) {
                // Not found
                return false;
            }
        }

        if (inputStream != null) {
            try {
                inputStream.close();
            } catch (IOException e) {
                // Ignored
            }
        }

        return inputStream != null;
    }

    @Keep
    public GameInfo getGameInfo() {
        return currentGameInfo;
    }

    @Keep
    public void vibrate(double seconds) {
        if (vibrator != null) {
            long duration = (long) (seconds * 1000.);
            if (android.os.Build.VERSION.SDK_INT >= 26) {
                VibrationEffect ve = VibrationEffect.createOneShot(duration, VibrationEffect.DEFAULT_AMPLITUDE);
                vibrator.vibrate(ve);
            } else {
                vibrator.vibrate(duration);
            }
        }
    }

    @Keep
    public boolean openURLFromLOVE(String url) {
        Log.d(TAG, "opening url = " + url);
        return openURL(url) == 0;
    }

    @Keep
    public boolean hasBackgroundMusic() {
        AudioManager audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        return audioManager.isMusicActive();
    }

    @Keep
    public String[] buildFileTree() {
        // Map key is path, value is directory flag
        HashMap<String, Boolean> map = buildFileTree(getAssets(), "", new HashMap<>());
        ArrayList<String> result = new ArrayList<>();

        for (Map.Entry<String, Boolean> data: map.entrySet()) {
            result.add((data.getValue() ? "d" : "f") + data.getKey());
        }

        String[] r = new String[result.size()];
        result.toArray(r);
        return r;
    }

    @Keep
    public float getDPIScale() {
        DisplayMetrics metrics = getResources().getDisplayMetrics();
        return metrics.density;
    }

    @Keep
    public Rect getSafeArea() {
        Rect rect = null;

        if (android.os.Build.VERSION.SDK_INT >= 28) {
            DisplayCutout cutout = getWindow().getDecorView().getRootWindowInsets().getDisplayCutout();

            if (cutout != null) {
                rect = new Rect();
                rect.set(
                    cutout.getSafeInsetLeft(),
                    cutout.getSafeInsetTop(),
                    cutout.getSafeInsetRight(),
                    cutout.getSafeInsetBottom()
                );
            }
        }

        return rect;
    }

    @Keep
    public String getCRequirePath() {
        ApplicationInfo applicationInfo = getApplicationInfo();

        if (isNativeLibsExtracted()) {
            return applicationInfo.nativeLibraryDir + "/?.so";
        } else {
            // The native libs are inside the APK and can be loaded directly.
            // FIXME: What about split APKs?
            String abi = android.os.Build.SUPPORTED_ABIS[0];
            return applicationInfo.sourceDir + "!/lib/" + abi + "/?.so";
        }
    }

    @Keep
    public void setImmersiveMode(boolean enable) {
        if (android.os.Build.VERSION.SDK_INT >= 28) {
            WindowManager.LayoutParams attr = getWindow().getAttributes();

            if (enable) {
                attr.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            } else {
                attr.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_NEVER;
            }
        }

        shortEdgesMode = enable;
    }

    @Keep
    public boolean getImmersiveMode() {
        return shortEdgesMode;
    }

    public int getAudioSMP() {
        int smp = 256;
        AudioManager a = (AudioManager) getSystemService(Context.AUDIO_SERVICE);

        if (a != null) {
            int b = Integer.parseInt(a.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER));
            smp = b > 0 ? b : smp;
        }

        return smp;
    }

    public int getAudioFreq() {
        int freq = 44100;
        AudioManager a = (AudioManager) getSystemService(Context.AUDIO_SERVICE);

        if (a != null) {
            int b = Integer.parseInt(a.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE));
            freq = b > 0 ? b : freq;
        }

        return freq;
    }

    public boolean isNativeLibsExtracted() {
        if (android.os.Build.VERSION.SDK_INT >= 23) {
            ApplicationInfo appInfo = getApplicationInfo();
            return (appInfo.flags & ApplicationInfo.FLAG_EXTRACT_NATIVE_LIBS) != 0;
        }

        return false;
    }

    public void sendFileDescriptorAsDroppedFile(int fd) {
        if (fd != -1) {
            SDLActivity.onNativeDropFile("love2d://fd/" + fd);
        }
    }

    private void handleIntent(Intent intent) {
        Uri game = intent.getData();
        if (game == null) {
            return;
        }

        if (mSingleton == null) {
            // Game is not running, consider setting the currentGameInfo here

            if (hasEmbeddedGame()) {
                // Send it as dropped file later
                delayedFd = convertToFileDescriptor(game);
            } else {
                // Process to GameInfo
                processOpenGame(intent, game);
            }
        } else {
            // Game is already running. Send it as dropped file.
            int fd = convertToFileDescriptor(game);
            sendFileDescriptorAsDroppedFile(fd);
        }
    }

    private HashMap<String, Boolean> buildFileTree(AssetManager assetManager, String dir, HashMap<String, Boolean> map) {
        String strippedDir = dir.endsWith("/") ? dir.substring(0, dir.length() - 1) : dir;

        // Try open dir
        try {
            InputStream test = assetManager.open(strippedDir);
            // It's a file
            test.close();
            map.put(strippedDir, false);
        } catch (FileNotFoundException e) {
            // It's a directory
            String[] list = null;

            // List files
            try {
                list = assetManager.list(strippedDir);
            } catch (IOException e2) {
                Log.e(TAG, strippedDir, e2);
            }

            // Mark as file
            map.put(dir, true);

            // This Object comparison is intentional.
            if (strippedDir != dir) {
                map.put(strippedDir, true);
            }

            if (list != null) {
                for (String path: list) {
                    buildFileTree(assetManager, dir + path + "/", map);
                }
            }
        } catch (IOException e) {
            Log.e(TAG, dir, e);
        }

        return map;
    }

    private int convertToFileDescriptor(Uri uri) {
        try {
            ParcelFileDescriptor pfd = getContentResolver().openFileDescriptor(uri, "r");
            return pfd.dup().detachFd();
        } catch (IOException e) {
            Log.d(TAG, "Failed attempt to convert " + uri.toString() + " to file descriptor", e);
        }

        return -1;
    }

    private void processOpenGame(Intent intent, Uri game) {
        String scheme = game.getScheme();
        String path = game.getPath();

        if (scheme.equals("content")) {
            // The intent may have more information about the filename
            currentGameInfo.identity = intent.getStringExtra("name");

            if (currentGameInfo.identity == null) {
                // Use "lovegame" as fallback
                // TODO: Use the content URI basename
                Log.w(TAG, "Using \"lovegame\" as fallback for game identity (Uri " + game + ")");
                currentGameInfo.identity = "lovegame";
            }

            currentGameInfo.fd = convertToFileDescriptor(game);
        } else if (scheme.equals("file")) {
            File f = new File(path);
            currentGameInfo.path = path;
            currentGameInfo.identity = f.getName();
        }
    }
}
