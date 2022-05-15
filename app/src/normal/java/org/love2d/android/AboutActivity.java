package org.love2d.android;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

public class AboutActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_about);

        // Set button click listener
        Button button = findViewById(R.id.button);
        button.setOnClickListener(v -> {
            Uri uri = Uri.parse("https://love2d.org/");
            Intent intent = new Intent(Intent.ACTION_VIEW, uri);
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(intent);
        });

        // Set version
        TextView versionText = findViewById(R.id.textView4);
        versionText.setText(getString(R.string.version_info, BuildConfig.VERSION_NAME));
    }
}
