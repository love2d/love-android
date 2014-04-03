package org.love2d.android;

import org.libsdl.app.SDLActivity;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

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
import android.util.Log;
import android.util.DisplayMetrics;
import android.widget.Toast;

public class GameActivity extends SDLActivity {
    private static DisplayMetrics metrics = new DisplayMetrics();
    private static String gamePath = "";
    private static Context context;
  
    @Override
    protected void onCreate(Bundle savedInstanceState) {
      Log.d("GameActivity", "started");

      context = this.getApplicationContext();

      Uri game = this.getIntent().getData();
      if (game != null) {
        if (game.getScheme().equals ("file")) {
          gamePath = game.getPath();
        } else {
          copyGameToCache (game);
        }
        Log.d("GameActivity", "Selected the file: " + getGamePath());
      }

      super.onCreate(savedInstanceState);
      getWindowManager().getDefaultDisplay().getMetrics(metrics);
    }

    public static String getGamePath() {
      Log.d ("GameActivity", "called getGamePath(), game path = " + gamePath);
        return gamePath;
    }

    public static DisplayMetrics getMetrics() {
        return metrics;
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
