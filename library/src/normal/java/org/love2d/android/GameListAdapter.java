/*
 * Copyright (c) 2006-2024 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

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
