package org.love2d.android;

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

        return holder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        Data data = this.data[position];
        holder.setName(data.path.getName());
        holder.setIsDirectory(data.directory);
    }

    @Override
    public int getItemCount() {
        return data != null ? data.length : 0;
    }

    public void setData(Data[] data) {
        this.data = data;
    }

    static class ViewHolder extends RecyclerView.ViewHolder {

        private final TextView name;
        private final ImageView image;

        public ViewHolder(View itemView) {
            super(itemView);

            name = itemView.findViewById(R.id.textView);
            image = itemView.findViewById(R.id.imageView);
        }

        public void setName(String name) {
            this.name.setText(name);
        }

        public void setIsDirectory(boolean directory) {
            this.image.setImageResource(directory ? R.drawable.ic_baseline_folder_32 : R.drawable.ic_baseline_insert_drive_file_32);
        }
    }

    static class Data {
        // Absolute path of the file.
        public File path;
        // Denote if this game is a directory.
        public boolean directory;
    }
}
