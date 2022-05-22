package org.love2d.android;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.io.File;

public class GameListAdapter extends RecyclerView.Adapter<GameListAdapter.ViewHolder> {

    private Data[] data = null;

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.row_game, parent, false);
        ViewHolder holder = new ViewHolder(view);
        view.setOnClickListener(holder);

        return holder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        holder.setData(this.data[position]);
    }

    @Override
    public int getItemCount() {
        return data != null ? data.length : 0;
    }

    public void setData(Data[] data) {
        this.data = data;
    }

    static class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

        private final TextView name;
        private final ImageView image;
        private File file;

        public ViewHolder(View itemView) {
            super(itemView);

            name = itemView.findViewById(R.id.textView);
            image = itemView.findViewById(R.id.imageView);
        }

        public void setData(Data data) {
            name.setText(data.path.getName());
            image.setImageResource(data.directory ? R.drawable.ic_baseline_folder_32 : R.drawable.ic_baseline_insert_drive_file_32);
            file = data.path;
        }

        @Override
        public void onClick(View v) {
            if (file == null) {
                return;
            }

            Context context = v.getContext();
            Intent intent = new Intent(context, GameActivity.class);
            intent.setData(Uri.fromFile(file));
            context.startActivity(intent);
        }
    }

    static class Data {
        // Absolute path of the file.
        public File path;
        // Denote if this game is a directory.
        public boolean directory;
    }
}
