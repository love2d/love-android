package org.love2d.android;

import java.io.File;

public class GameListItem {
    final String name;
    final File file;
    final boolean dir;

    public GameListItem(String name, File file, boolean dir) {
        this.name = name;
        this.file = file;
        this.dir = dir;
    }

    public GameListItem(File file) {
        this(file.getName(), file, file.isDirectory());
    }
}
