package org.love2d.android;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SwipeRefreshLayout swipeLayout = findViewById(R.id.swipeRefreshLayout);
        swipeLayout.setOnRefreshListener(() -> {
            // TODO: Actually update list of games
            swipeLayout.setRefreshing(false);
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.options_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int itemId = item.getItemId();

        // Handle item selection
        if (itemId == R.id.optionItem) {
            Intent intent = new Intent(this, GameActivity.class);
            startActivity(intent);
            return true;
        } else if (itemId == R.id.optionItem2) {
            getGameFolderDialog().show();
            return true;
        } else if (itemId == R.id.optionItem3) {
            Intent intent = new Intent(this, AboutActivity.class);
            startActivity(intent);
            return true;
        } else {
            return super.onOptionsItemSelected(item);
        }
    }

    private AlertDialog getGameFolderDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this)
            .setTitle(getString(R.string.game_folder))
            .setPositiveButton(R.string.ok, (dialog1, which) -> { });
        StringBuilder message = new StringBuilder()
            .append(getString(R.string.game_folder_location, getPackageName()))
            .append("\n\n");

        if (Build.VERSION.SDK_INT >= 30) {
            message.append(getString(R.string.game_folder_inaccessible));
        } else {
            message.append(getString(R.string.game_folder_accessible));
        }

        return builder.setMessage(message.toString()).create();
    }
}
