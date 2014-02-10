package org.love2d.android;

import org.libsdl.app.SDLActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;

public class GameActivity extends SDLActivity {
    private static DisplayMetrics metrics = new DisplayMetrics();
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
    }
    
    public static DisplayMetrics getMetrics() {
        return metrics;
    }
}
