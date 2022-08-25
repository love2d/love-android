package org.love2d.android;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.ListView;

import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.zip.ZipFile;

public class MainActivity extends Activity {
    private static final String TAG = "MainActivity";
    private static final Integer INTENT_OK = 1024;

    private final Executor executor = Executors.newSingleThreadExecutor();

    public static boolean isValidLovegame(File file) {
        boolean valid = false;
        if (file == null)
            return false;

        try {
            ZipFile zip = new ZipFile(file, ZipFile.OPEN_READ);
            valid = zip.getEntry("main.lua") != null;
            zip.close();
        } catch (IOException ignored) {
        }

        return valid;
    }

    public static boolean isValidGamedir(File file) {
        File mainLua = new File(file, "main.lua");
        return mainLua.isFile();
    }

    private void openFileLauncher() {
        Intent doc = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        doc.setType("*/*");
        doc.addCategory(Intent.CATEGORY_OPENABLE);
        doc.setFlags(
                Intent.FLAG_GRANT_READ_URI_PERMISSION | Intent.FLAG_GRANT_PERSISTABLE_URI_PERMISSION);
        startActivityForResult(doc, INTENT_OK);
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == INTENT_OK && resultCode == RESULT_OK && data != null) {
            Uri result = data.getData();
            Intent open = new Intent(this, GameActivity.class);
            open.setData(result);
            startActivity(open);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ListView gameList = findViewById(R.id.gamesList);
        SwipeRefreshLayout swipeLayout = findViewById(R.id.swipeRefresh);
        LinearLayout noGameText = findViewById(R.id.nogameText);

        GameListAdapter adapter = new GameListAdapter(new ArrayList<>(), this);

        // Set refresh listener
        swipeLayout.setOnRefreshListener(() -> scanGames(adapter, noGameText, swipeLayout));
        scanGames(adapter, noGameText, null);

        // Set layout manager and adapter
        gameList.setAdapter(adapter);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.options_menu, menu);
        return true;
    }

    @Override
    @SuppressLint("NonConstantResourceId")
    public boolean onOptionsItemSelected(MenuItem item) {
        int itemId = item.getItemId();

        // Handle item selection
        switch (itemId) {
            case R.id.optionItem:
                openFileLauncher();
                return true;
            case R.id.optionItem2: {
                Intent intent = new Intent(this, GameActivity.class);
                startActivity(intent);
                return true;
            }
            case R.id.optionItem3:
                getGameFolderDialog().show();
                return true;
            case R.id.optionItem4: {
                Intent intent = new Intent(this, AboutActivity.class);
                startActivity(intent);
                return true;
            }
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private AlertDialog getGameFolderDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);

        StringBuilder message = new StringBuilder()
                .append(getString(R.string.game_folder_location, getPackageName()))
                .append("\n\n");

        if (Build.VERSION.SDK_INT >= 30)
            message.append(getString(R.string.game_folder_inaccessible));
        else
            message.append(getString(R.string.game_folder_accessible));

        return builder
                .setTitle(getString(R.string.game_folder))
                .setMessage(message.toString())
                .create();
    }

    private void scanGames(GameListAdapter adapter, LinearLayout noGameText, SwipeRefreshLayout swipeRefreshLayout) {
        executor.execute(() -> {
            File extDir = getExternalFilesDir("games");

            if (!extDir.isDirectory()) {
                if (!extDir.mkdir()) {
                    // Scan failure, abort
                    runOnUiThread(() -> {
                        if (swipeRefreshLayout != null)
                            swipeRefreshLayout.setRefreshing(false);
                    });

                    Log.e(TAG, "Directory creation failure.");
                    return;
                }
            }

            ArrayList<GameListItem> validGames = new ArrayList<>();
            File[] files = extDir.listFiles();

            if (files != null) {
                for (File file : files) {
                    GameListItem data = null;

                    if ((file.isDirectory() && isValidGamedir(file)) || isValidLovegame(file))
                        data = new GameListItem(file);

                    if (data != null)
                        validGames.add(data);
                }
            }

            boolean empty = validGames.isEmpty();

            runOnUiThread(() -> {
                if (empty)
                    adapter.setData(null);
                else
                    adapter.setData(validGames);

                adapter.notifyDataSetChanged();

                if (swipeRefreshLayout != null)
                    swipeRefreshLayout.setRefreshing(false);

                noGameText.setVisibility(empty ? View.VISIBLE : View.INVISIBLE);
            });
        });
    }
}
