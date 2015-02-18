package org.love2d.android;

import org.libsdl.app.SDLActivity;

import java.util.List;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import android.app.Activity;
import android.app.DownloadManager;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.PowerManager;
import android.os.ResultReceiver;
import android.os.Vibrator;
import android.util.Log;
import android.util.DisplayMetrics;
import android.widget.Toast;
import android.view.*;

public class GameActivity extends SDLActivity {
    private static DisplayMetrics metrics = new DisplayMetrics();
    private static String gamePath = "";
    private static Context context;
    private static Vibrator vibrator;
    private static boolean immersiveActive = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
      Log.d("GameActivity", "started");
 
      context = this.getApplicationContext();
      vibrator = (Vibrator) this.context.getSystemService(Context.VIBRATOR_SERVICE);

      handleIntent (this.getIntent());

      super.onCreate(savedInstanceState);
      getWindowManager().getDefaultDisplay().getMetrics(metrics);
    }

    @Override
    protected void onNewIntent (Intent intent) {
      Log.d("GameActivity", "onNewIntent() with " + intent);
      handleIntent (intent);
      resetNative();
      startNative();
    };

    protected void handleIntent (Intent intent) {
      Uri game = intent.getData();
      if (game != null) {
        if (game.getScheme().equals ("file")) {
          Log.d("GameActivity", "Received intent with path: " + game.getPath());

          // If we were given the path of a main.lua then use its
          // directory. Otherwise use full path.
          List<String> path_segments = game.getPathSegments();
          if (path_segments.get(path_segments.size() - 1).equals("main.lua")) {
            gamePath = game.getPath().substring(0, game.getPath().length() - "main.lua".length());
          } else {
            gamePath = game.getPath();
          }
        } else {
          copyGameToCache (game);
        }

        Log.d("GameActivity", "new gamePath: " + gamePath);
      }
    };

    @Override
    protected void onDestroy() {
      Log.d("GameActivity", "Cancelling vibration");
      vibrator.cancel();
      super.onDestroy();
    }

    @Override
    protected void onPause() {
      Log.d("GameActivity", "Cancelling vibration");
      vibrator.cancel();
      super.onPause();
    }

    @Override
    public void onResume() {
      super.onResume();

      if (immersiveActive) {
        getWindow().getDecorView().setSystemUiVisibility(
            View.SYSTEM_UI_FLAG_LAYOUT_STABLE
            | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
            | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
            | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
            | View.SYSTEM_UI_FLAG_FULLSCREEN
            | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY);
      }
    }

    public void setImmersiveMode (boolean immersive_mode) {
      immersiveActive = immersive_mode;

      final Object lock = new Object();
      final boolean immersive_enabled = immersive_mode;
      synchronized (lock) {
        runOnUiThread (new Runnable() {
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
      };
    }

    public boolean getImmersiveMode () {
      return immersiveActive;
    }

    public static String getGamePath() {
      Log.d ("GameActivity", "called getGamePath(), game path = " + gamePath);
      return gamePath;
    }

    public static DisplayMetrics getMetrics() {
        return metrics;
    }

    public static void vibrate (double seconds) {
      vibrator.vibrate((long) (seconds * 1000.));
    }

    public static void openURL (String url) {
      Log.d ("GameActivity", "opening url = " + url);
      Intent i = new Intent(Intent.ACTION_VIEW);
      i.setData(Uri.parse(url));
      i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
      context.startActivity(i);
    }
  
    void copyGameToCache (Uri sourceuri)
    {
      String destinationFilename = this.getCacheDir().getPath()+"/downloaded.love";
      gamePath = destinationFilename;

      BufferedOutputStream bos = null;
      try {
        bos = new BufferedOutputStream(new FileOutputStream(destinationFilename, false));
      } catch (IOException e) {
        Log.d ("GameActivity", "Could not open destination file:" + e.getMessage());
      }

      int chunk_read = 0;
      int bytes_written = 0;

      BufferedInputStream bis = null;
      if (sourceuri.getScheme().equals("content")) {
        try {
          bis = new BufferedInputStream(getContentResolver().openInputStream(sourceuri));
        } catch (IOException e) {
          Log.d ("GameActivity", "Could not open game file:" + e.getMessage());
        }
      } else {
        Log.d ("GameActivity", "Unsupported scheme: " + sourceuri.getScheme());
      }

      if (bis != null) {
        // actual copying
        try {
          byte[] buf = new byte[1024];
          chunk_read = bis.read(buf);
          do {
            bos.write(buf, 0, chunk_read);
            bytes_written += chunk_read;
            chunk_read = bis.read(buf);        
          } while(chunk_read != -1);
        } catch (IOException e) {
          Log.d ("GameActivity", "Copying failed:" + e.getMessage());
        } 
      }

      // close streams
      try {
        if (bis != null) bis.close();
        if (bos != null) bos.close();
      } catch (IOException e) {
        Log.d ("GameActivity", "Copying failed: " + e.getMessage());
      }

      Log.d("GameActivity", "Copied " + bytes_written + " bytes");
    }
}
