package org.love2d.android;

import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

public class GameLauncher extends GameActivity {

    private static String gamePath;

    @Override
    protected void onCreate(Bundle bundle) {
        Uri game = this.getIntent().getData();
        if (game != null) {
            gamePath = game.getPath();
            Log.d("GameLauncher", "Selected the file: " + gamePath);
        }
        super.onCreate(bundle);
    }

    public static String getGamePath() {
        return gamePath;
    }
}
