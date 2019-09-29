package org.love2d.android;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.Manifest;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;

import androidx.core.app.ActivityCompat;

public class DownloadActivity extends Activity {
    public static final int EXTERNAL_STORAGE_REQUEST_CODE = 3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        if (android.os.Build.VERSION.SDK_INT >= 29 ||
            ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED)
        {
            runDownloader();
            finish();
        } else {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, EXTERNAL_STORAGE_REQUEST_CODE);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (grantResults.length > 0) {
            Log.d("DownloadActivity", "Received a request permission result");

            if (requestCode == EXTERNAL_STORAGE_REQUEST_CODE) {
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    runDownloader();
                    finish();
                } else {
                    Log.d("DownloadActivity", "Did not get permission.");
                    if (ActivityCompat.shouldShowRequestPermissionRationale(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)) {
                        showExternalStoragePermissionMissingDialog();
                    }
                }
            }
        }
    }

    protected void showExternalStoragePermissionMissingDialog() {
        AlertDialog dialog = new AlertDialog.Builder(this)
            .setTitle("Storage Permission Missing")
            .setMessage("LÖVE for Android will not be able to download games without storage permission.")
            .setNeutralButton("Continue", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int whichButton) {
                    dialog.dismiss();
                    finish();
                }
            })
            .create();
        dialog.show();
    }

    protected void runDownloader()
    {
        Intent intent = getIntent();
        
        if (intent != null) {
            Uri uri = intent.getData();
            Intent targetIntent = new Intent(this, DownloadService.class);
            targetIntent.putExtra("url", uri.toString());
            startService(targetIntent);
        }
    }
}
