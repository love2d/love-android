package org.love2d.android;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

import androidx.annotation.Nullable;

public class IntentReceiverActivity extends Activity {
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent mainIntent = getIntent();
        Intent intent = new Intent(this, GameActivity.class);

        if (mainIntent
                .getAction()
                .equals(Intent.ACTION_SEND)) {
            // Convert to simpler intent that our GameActivity can process.
            Uri uri = mainIntent.getParcelableExtra(Intent.EXTRA_STREAM);
            intent.setData(uri);
            intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
        }

        startActivity(intent);
        finish();
    }
}
