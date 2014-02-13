package org.love2d.android;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

public class GameLauncher extends GameActivity {

    private static String gamePath;

    @Override
    protected void onCreate(Bundle bundle) {
        Uri game = this.getIntent().getData();
        if (game != null) {
					if (game.getScheme().equals ("file")) {
						gamePath = game.getPath();
					} else {
	          copyGameToCache (game);
					}
          Log.d("GameLauncher", "Selected the file: " + getGamePath());
        }
        super.onCreate(bundle);
    }

    public static String getGamePath() {
        return gamePath;
    }
	
    void copyGameToCache (Uri sourceuri)
    {
    	String destinationFilename = this.getCacheDir().getPath()+"/downloaded.love";
    	gamePath = destinationFilename;

    	BufferedOutputStream bos = null;
    	try {
    		bos = new BufferedOutputStream(new FileOutputStream(destinationFilename, false));
    	} catch (IOException e) {
    		Log.d ("GameLauncher", "Could not open destination file:" + e.getMessage());
    	}

    	int chunk_read = 0;
    	int bytes_written = 0;

    	BufferedInputStream bis = null;
    	if (sourceuri.getScheme().equals("content")) {
    		try {
    			bis = new BufferedInputStream(getContentResolver().openInputStream(sourceuri));
    		} catch (IOException e) {
    			Log.d ("GameLauncher", "Could not open game file:" + e.getMessage());
    		}
    	} else {
    		Log.d ("GameLauncher", "Unsupported scheme: " + sourceuri.getScheme());
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
    			Log.d ("GameLauncher", "Copying failed:" + e.getMessage());
    		} 
    	}

    	// close streams
    	try {
    		if (bis != null) bis.close();
    		if (bos != null) bos.close();
    	} catch (IOException e) {
    		Log.d ("GameLauncher", "Copying failed: " + e.getMessage());
    	}

    	Log.d("GameLauncher", "Copied " + bytes_written + " bytes");
    }

}
