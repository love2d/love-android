package org.love2d.android;

import org.libsdl.app.SDLActivity;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.DownloadManager;
import android.app.ProgressDialog;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.ResultReceiver;
import android.util.Log;
import android.util.DisplayMetrics;

public class GameActivity extends SDLActivity {
    private static DisplayMetrics metrics = new DisplayMetrics();
    private static String gamePath = "";
	// declare the dialog as a member field of your activity
	private static ProgressDialog mProgressDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
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
      } else if (sourceuri.getScheme().equals("http")) {
    	  String url = sourceuri.getScheme() + "://" + sourceuri.getHost() + sourceuri.getPath();
    	  Log.d("GameActivity", "url = " + url);
    	  
    	  // instantiate it within the onCreate method
    	  mProgressDialog = new ProgressDialog(GameActivity.this);
    	  mProgressDialog.setMessage("Downloading Game");
    	  mProgressDialog.setIndeterminate(true);
    	  mProgressDialog.setProgressStyle(ProgressDialog.STYLE_HORIZONTAL);
    	  mProgressDialog.setCancelable(true);
    	  mProgressDialog.setProgress (0);
    	  mProgressDialog.setMax (100);
    	  
    	  // this is how you fire the downloader
    	  mProgressDialog.show();
    	  Intent intent = new Intent(this, DownloadService.class);
    	  intent.putExtra("url", url);
    	  intent.putExtra("receiver", new DownloadReceiver(new Handler()));
    	  startService(intent);
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

    private class DownloadReceiver extends ResultReceiver{
        public DownloadReceiver(Handler handler) {
            super(handler);
        }

        @Override
        protected void onReceiveResult(int resultCode, Bundle resultData) {
        	super.onReceiveResult(resultCode, resultData);

            if (resultCode == DownloadService.UPDATE_PROGRESS) {
          	    mProgressDialog.setIndeterminate(false);
                int progress = resultData.getInt("progress");
                mProgressDialog.setProgress(progress);
                if (progress == 100) {
                    mProgressDialog.dismiss();
                }
            }
        }
    }
}
