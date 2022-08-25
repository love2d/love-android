package org.love2d.android;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.File;
import java.util.ArrayList;

public class GameListAdapter extends ArrayAdapter<GameListItem> implements View.OnClickListener {
    private final Context context;

    public GameListAdapter(ArrayList<GameListItem> data, Context context) {
        super(context, R.layout.row_game, data);
        this.context = context;
    }

    public void setData(ArrayList<GameListItem> data) {
        clear();
        if (data == null)
            return;
        for (GameListItem item : data)
            add(item);
    }

    @Override
    public void onClick(View v) {
        ViewHolder item = (ViewHolder) v.getTag();
        if (item.file == null)
            return;

        Intent intent = new Intent(context, GameActivity.class);
        intent.setData(Uri.fromFile(item.file));
        context.startActivity(intent);
    }

    @Override
    public View getView(int position, View view, ViewGroup parent) {
        GameListItem item = getItem(position);
        ViewHolder holder;

        if (view == null) {
            holder = new ViewHolder();
            LayoutInflater inflater = LayoutInflater.from(getContext());
            view = inflater.inflate(R.layout.row_game, parent, false);
            holder.name = view.findViewById(R.id.gameName);
            holder.image = view.findViewById(R.id.gameImage);
            holder.file = item.file;
            view.setTag(holder);
            view.setOnClickListener(this);
        } else
            holder = (ViewHolder) view.getTag();

        holder.name.setText(item.name);
        holder.image.setImageResource(
                item.dir ? R.drawable.ic_baseline_folder_32 : R.drawable.ic_baseline_insert_drive_file_32);
        return view;
    }

    private static class ViewHolder {
        TextView name;
        ImageView image;
        File file;
    }
}
