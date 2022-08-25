package org.love2d.android;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

public class AboutActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);

        // Set button click listener
        Button button = findViewById(R.id.websiteButton);
        button.setOnClickListener(v -> {
            Uri uri = Uri.parse("https://love2d.org/");
            Intent intent = new Intent(Intent.ACTION_VIEW, uri);
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(intent);
        });

        // Set version
        TextView versionText = findViewById(R.id.versionInfo);
        versionText.setText(getString(R.string.version_info, BuildConfig.VERSION_NAME));
    }
}
