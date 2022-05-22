package org.love2d.android;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.content.Intent;
import android.os.Build;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;
import java.util.zip.ZipFile;

public class MainActivity extends AppCompatActivity {

    private Executor executor = Executors.newSingleThreadExecutor();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        RecyclerView recyclerView = findViewById(R.id.recyclerView);
        SwipeRefreshLayout swipeLayout = findViewById(R.id.swipeRefreshLayout);
        ConstraintLayout noGameText = findViewById(R.id.constraintLayout);

        GameListAdapter adapter = new GameListAdapter();

            // Set refresh listener
        swipeLayout.setOnRefreshListener(() -> {
            scanGames(adapter, noGameText, swipeLayout);
        });

        // Set layout manager and adapter
        recyclerView.setLayoutManager(new LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false));
        recyclerView.setAdapter(adapter);

        scanGames(adapter, noGameText, null);
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

    private void scanGames(GameListAdapter adapter, ConstraintLayout noGameText, SwipeRefreshLayout swipeRefreshLayout) {
        final MainActivity current = this;

        executor.execute(() -> {
            File extDir = getExternalFilesDir("games");

            if (!extDir.isDirectory()) {
                if (!extDir.mkdir()) {
                    // Scan failure, abort
                    if (swipeRefreshLayout != null) {
                        swipeRefreshLayout.setRefreshing(false);
                    }

                    new AlertDialog.Builder(current)
                        .setTitle("Scan error")
                        .setMessage("Scan failure")
                        .setPositiveButton(R.string.ok, (dialog1, which) -> { })
                        .create()
                        .show();
                    return;
                }
            }

            ArrayList<GameListAdapter.Data> validGames = new ArrayList<>();
            File[] files = extDir.listFiles();

            if (files != null) {
                for (File file: files) {
                    GameListAdapter.Data gameData = null;

                    if (file.isDirectory()) {
                        if (isValidGamedir(file)) {
                            gameData = new GameListAdapter.Data();
                            gameData.path = file;
                            gameData.directory = true;
                        }
                    } else {
                        if (isValidLovegame(file)) {
                            gameData = new GameListAdapter.Data();
                            gameData.path = file;
                            gameData.directory = false;
                        }
                    }

                    if (gameData != null) {
                        validGames.add(gameData);
                    }
                }
            }

            boolean empty = validGames.isEmpty();

            runOnUiThread(() -> {
                if (empty) {
                    adapter.setData(null);
                } else {
                    GameListAdapter.Data[] gameDatas = new GameListAdapter.Data[validGames.size()];
                    validGames.toArray(gameDatas);
                    adapter.setData(gameDatas);
                }

                adapter.notifyDataSetChanged();

                if (swipeRefreshLayout != null) {
                    swipeRefreshLayout.setRefreshing(false);
                }

                noGameText.setVisibility(empty ? View.VISIBLE : View.INVISIBLE);
            });
        });
    }

    public static boolean isValidLovegame(File file) {
        boolean valid = false;

        try {
            ZipFile zip = new ZipFile(file, ZipFile.OPEN_READ);
            valid = zip.getEntry("main.lua") != null;
            zip.close();
        } catch (IOException ignored) { }

        return valid;
    }

    public static boolean isValidGamedir(File file) {
        File mainLua = new File(file, "main.lua");
        return mainLua.isFile();
    }
}
