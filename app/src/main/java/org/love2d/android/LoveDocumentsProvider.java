/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


package org.love2d.android;

import static android.os.Build.VERSION.SDK_INT;

import android.content.res.AssetFileDescriptor;
import android.database.Cursor;
import android.database.MatrixCursor;
import android.graphics.Point;
import android.os.Build;
import android.os.CancellationSignal;
import android.os.Handler;
import android.os.ParcelFileDescriptor;
import android.provider.DocumentsContract.Document;
import android.provider.DocumentsContract.Root;
import android.provider.DocumentsProvider;
import android.util.Log;
import android.webkit.MimeTypeMap;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Set;

/**
 * Manages documents and exposes them to the Android system for sharing.
 */
public class LoveDocumentsProvider extends DocumentsProvider {
    private static final String TAG = "LoveDocumentsProvider";

    // Use these as the default columns to return information about a root if no specific
    // columns are requested in a query.
    private static final String[] DEFAULT_ROOT_PROJECTION = new String[]{
            Root.COLUMN_ROOT_ID,
            Root.COLUMN_MIME_TYPES,
            Root.COLUMN_FLAGS,
            Root.COLUMN_ICON,
            Root.COLUMN_TITLE,
            Root.COLUMN_SUMMARY,
            Root.COLUMN_DOCUMENT_ID,
            Root.COLUMN_AVAILABLE_BYTES
    };

    // Use these as the default columns to return information about a document if no specific
    // columns are requested in a query.
    private static final String[] DEFAULT_DOCUMENT_PROJECTION = new String[]{
            Document.COLUMN_DOCUMENT_ID,
            Document.COLUMN_MIME_TYPE,
            Document.COLUMN_DISPLAY_NAME,
            Document.COLUMN_LAST_MODIFIED,
            Document.COLUMN_FLAGS,
            Document.COLUMN_SIZE
    };

    // No official policy on how many to return, but make sure you do limit the number of recent
    // and search results.
    private static final int MAX_SEARCH_RESULTS = 20;
    private static final int MAX_LAST_MODIFIED = 5;

    private static final String ROOT = "root";

    // A file object at the root of the file hierarchy.  Depending on your implementation, the root
    // does not need to be an existing file system directory.  For example, a tag-based document
    // provider might return a directory containing all tags, represented as child directories.
    private File mBaseDir;

    @Override
    public boolean onCreate() {
        Log.v(TAG, "onCreate");

        mBaseDir = getContext().getExternalFilesDir(null);
        return true;
    }

    // BEGIN_INCLUDE(query_roots)
    @Override
    public Cursor queryRoots(String[] projection) throws FileNotFoundException {
        Log.v(TAG, "queryRoots");

        // Create a cursor with either the requested fields, or the default projection.  This
        // cursor is returned to the Android system picker UI and used to display all roots from
        // this provider.
        final MatrixCursor result = new MatrixCursor(resolveRootProjection(projection));

        // It's possible to have multiple roots (e.g. for multiple accounts in the same app) -
        // just add multiple cursor rows.
        // Construct one row for a root called "MyCloud".
        final MatrixCursor.RowBuilder row = result.newRow();

        row.add(Root.COLUMN_ROOT_ID, ROOT);
        row.add(Root.COLUMN_SUMMARY, null);

        // FLAG_SUPPORTS_CREATE means at least one directory under the root supports creating
        // documents.  FLAG_SUPPORTS_RECENTS means your application's most recently used
        // documents will show up in the "Recents" category.  FLAG_SUPPORTS_SEARCH allows users
        // to search all documents the application shares. FLAG_SUPPORTS_IS_CHILD allows
        // testing parent child relationships, available after SDK 21 (Lollipop).
        if (SDK_INT < Build.VERSION_CODES.LOLLIPOP) {
            row.add(Root.COLUMN_FLAGS, Root.FLAG_SUPPORTS_CREATE |
                    Root.FLAG_SUPPORTS_RECENTS |
                    Root.FLAG_SUPPORTS_SEARCH);
        } else {
            row.add(Root.COLUMN_FLAGS, Root.FLAG_SUPPORTS_CREATE |
                    Root.FLAG_SUPPORTS_RECENTS |
                    Root.FLAG_SUPPORTS_SEARCH |
                    Root.FLAG_SUPPORTS_IS_CHILD);
        }

        // COLUMN_TITLE is the root title (e.g. what will be displayed to identify your provider).
        row.add(Root.COLUMN_TITLE, getContext().getApplicationInfo().loadLabel(getContext().getPackageManager()).toString());

        // This document id must be unique within this provider and consistent across time.  The
        // system picker UI may save it and refer to it later.
        row.add(Root.COLUMN_DOCUMENT_ID, getDocIdForFile(mBaseDir));

        // The child MIME types are used to filter the roots and only present to the user roots
        // that contain the desired type somewhere in their file hierarchy.
        row.add(Root.COLUMN_MIME_TYPES, getChildMimeTypes(mBaseDir));
        row.add(Root.COLUMN_AVAILABLE_BYTES, mBaseDir.getFreeSpace());
        row.add(Root.COLUMN_ICON, R.drawable.love);

        return result;
    }
    // END_INCLUDE(query_roots)

    // BEGIN_INCLUDE(query_recent_documents)
    @Override
    public Cursor queryRecentDocuments(String rootId, String[] projection)
            throws FileNotFoundException {
        Log.v(TAG, "queryRecentDocuments");

        // This example implementation walks a local file structure to find the most recently
        // modified files.  Other implementations might include making a network call to query a
        // server.

        // Create a cursor with the requested projection, or the default projection.
        final MatrixCursor result = new MatrixCursor(resolveDocumentProjection(projection));

        final File parent = getFileForDocId(rootId);

        // Create a queue to store the most recent documents, which orders by last modified.
        PriorityQueue<File> lastModifiedFiles = new PriorityQueue<File>(5, new Comparator<File>() {
            public int compare(File i, File j) {
                return Long.compare(i.lastModified(), j.lastModified());
            }
        });

        // Iterate through all files and directories in the file structure under the root.  If
        // the file is more recent than the least recently modified, add it to the queue,
        // limiting the number of results.
        final LinkedList<File> pending = new LinkedList<File>();

        // Start by adding the parent to the list of files to be processed
        pending.add(parent);

        // Do while we still have unexamined files
        while (!pending.isEmpty()) {
            // Take a file from the list of unprocessed files
            final File file = pending.removeFirst();
            if (file.isDirectory()) {
                // If it's a directory, add all its children to the unprocessed list
                Collections.addAll(pending, file.listFiles());
            } else {
                // If it's a file, add it to the ordered queue.
                lastModifiedFiles.add(file);
            }
        }

        // Add the most recent files to the cursor, not exceeding the max number of results.
        int includedCount = 0;
        while (includedCount < MAX_LAST_MODIFIED + 1 && !lastModifiedFiles.isEmpty()) {
            final File file = lastModifiedFiles.remove();
            includeFile(result, null, file);
            includedCount++;
        }
        return result;
    }
    // END_INCLUDE(query_recent_documents)

    // BEGIN_INCLUDE(query_search_documents)
    @Override
    public Cursor querySearchDocuments(String rootId, String query, String[] projection)
            throws FileNotFoundException {
        Log.v(TAG, "querySearchDocuments");

        // Create a cursor with the requested projection, or the default projection.
        final MatrixCursor result = new MatrixCursor(resolveDocumentProjection(projection));
        final File parent = getFileForDocId(rootId);

        // This example implementation searches file names for the query and doesn't rank search
        // results, so we can stop as soon as we find a sufficient number of matches.  Other
        // implementations might use other data about files, rather than the file name, to
        // produce a match; it might also require a network call to query a remote server.

        // Iterate through all files in the file structure under the root until we reach the
        // desired number of matches.
        final LinkedList<File> pending = new LinkedList<File>();

        // Start by adding the parent to the list of files to be processed
        pending.add(parent);

        // Do while we still have unexamined files, and fewer than the max search results
        while (!pending.isEmpty() && result.getCount() < MAX_SEARCH_RESULTS) {
            // Take a file from the list of unprocessed files
            final File file = pending.removeFirst();
            if (file.isDirectory()) {
                // If it's a directory, add all its children to the unprocessed list
                Collections.addAll(pending, file.listFiles());
            } else {
                // If it's a file and it matches, add it to the result cursor.
                if (file.getName().toLowerCase().contains(query)) {
                    includeFile(result, null, file);
                }
            }
        }
        return result;
    }
    // END_INCLUDE(query_search_documents)

    // BEGIN_INCLUDE(open_document_thumbnail)
    @Override
    public AssetFileDescriptor openDocumentThumbnail(String documentId, Point sizeHint,
                                                     CancellationSignal signal)
            throws FileNotFoundException {
        Log.v(TAG, "openDocumentThumbnail");

        final File file = getFileForDocId(documentId);
        final ParcelFileDescriptor pfd =
                ParcelFileDescriptor.open(file, ParcelFileDescriptor.MODE_READ_ONLY);
        return new AssetFileDescriptor(pfd, 0, AssetFileDescriptor.UNKNOWN_LENGTH);
    }
    // END_INCLUDE(open_document_thumbnail)

    // BEGIN_INCLUDE(query_document)
    @Override
    public Cursor queryDocument(String documentId, String[] projection)
            throws FileNotFoundException {
        Log.v(TAG, "queryDocument");

        // Create a cursor with the requested projection, or the default projection.
        final MatrixCursor result = new MatrixCursor(resolveDocumentProjection(projection));
        includeFile(result, documentId, null);
        return result;
    }
    // END_INCLUDE(query_document)

    // BEGIN_INCLUDE(query_child_documents)
    @Override
    public Cursor queryChildDocuments(String parentDocumentId, String[] projection,
                                      String sortOrder) throws FileNotFoundException {
        Log.v(TAG, "queryChildDocuments, parentDocumentId: " +
                parentDocumentId +
                " sortOrder: " +
                sortOrder);

        final MatrixCursor result = new MatrixCursor(resolveDocumentProjection(projection));
        final File parent = getFileForDocId(parentDocumentId);
        for (File file : parent.listFiles()) {
            includeFile(result, null, file);
        }
        return result;
    }
    // END_INCLUDE(query_child_documents)


    // BEGIN_INCLUDE(open_document)
    @Override
    public ParcelFileDescriptor openDocument(final String documentId, final String mode, CancellationSignal signal) throws FileNotFoundException {
        Log.v(TAG, "openDocument, mode: " + mode);

        final File file = getFileForDocId(documentId);
        final int accessMode = ParcelFileDescriptor.parseMode(mode);
        return ParcelFileDescriptor.open(file, accessMode);
    }
    // END_INCLUDE(open_document)

    public boolean isChildFile(File parentFile, File childFile) {
        File realFileParent = childFile.getParentFile();
        return realFileParent == null || realFileParent.equals(parentFile);
    }

    // BEGIN_INCLUDE(is_child_document)
    @Override
    public boolean isChildDocument(String parentDocumentId, String documentId) {
        Log.v(TAG, "isChildDocument");
        if(documentId.startsWith(parentDocumentId)) {
            return true;
        } else {
            return false;
        }
    }
    // END_INCLUDE(is_child_document)

    // BEGIN_INCLUDE(create_document)
    @Override
    public String createDocument(String documentId, String mimeType, String displayName)
            throws FileNotFoundException {
        Log.v(TAG, "createDocument");

        File parent = getFileForDocId(documentId);
        File file = new File(parent.getPath(), displayName);
        int conflictId = 1;
        while(file.exists()) {
            file = new File(parent.getPath(), displayName + "(" + conflictId++ + ")");
        }
        try {
            // Create the new File to copy into
            boolean wasNewFileCreated = false;
            if (Document.MIME_TYPE_DIR.equals(mimeType)) {
                wasNewFileCreated = file.mkdir();
            } else {
                wasNewFileCreated = file.createNewFile();
            }

            if (!wasNewFileCreated) {
                throw new FileNotFoundException("Failed to create document with name " +
                        displayName + " and documentId " + documentId);
            }
        } catch (IOException e) {
            throw new FileNotFoundException("Failed to create document with name " +
                    displayName + " and documentId " + documentId);
        }
        return getDocIdForFile(file);
    }
    // END_INCLUDE(create_document)

    // BEGIN_INCLUDE(rename_document)
    @Override
    public String renameDocument(String documentId, String displayName)
            throws FileNotFoundException {
        Log.v(TAG, "renameDocument");
        if (displayName == null) {
            throw new FileNotFoundException("Failed to rename document, new name is null");
        }

        // Create the destination file in the same directory as the source file
        File sourceFile = getFileForDocId(documentId);
        File sourceParentFile = sourceFile.getParentFile();
        if (sourceParentFile == null) {
            throw new FileNotFoundException("Failed to rename document. File has no parent.");
        }
        File destFile = new File(sourceParentFile.getPath(), displayName);

        // Try to do the rename
        try {
            boolean renameSucceeded = sourceFile.renameTo(destFile);
            if (!renameSucceeded) {
                throw new FileNotFoundException("Failed to rename document. Renamed failed.");
            }
        } catch (Exception e) {
            Log.w(TAG, "Rename exception : " + e.getLocalizedMessage() + e.getCause());
            throw new FileNotFoundException("Failed to rename document. Error: " + e.getMessage());
        }

        return getDocIdForFile(destFile);
    }
    // END_INCLUDE(rename_document)

    // BEGIN_INCLUDE(delete_document)
    @Override
    public void deleteDocument(String documentId) throws FileNotFoundException {
        Log.v(TAG, "deleteDocument");
        File file = getFileForDocId(documentId);
        if (file.delete()) {
            Log.i(TAG, "Deleted file with id " + documentId);
        } else {
            throw new FileNotFoundException("Failed to delete document with id " + documentId);
        }
    }
    // END_INCLUDE(delete_document)

    // BEGIN_INCLUDE(remove_document)
    @Override
    public void removeDocument(String documentId, String parentDocumentId)
            throws FileNotFoundException {
        Log.v(TAG, "removeDocument");
        File parent = getFileForDocId(parentDocumentId);
        File file = getFileForDocId(documentId);

        if (file == null) {
            throw new FileNotFoundException("Failed to delete document with id " + documentId);
        }

        // removeDocument is the same as deleteDocument but allows the parent to be specified
        // Check here if the specified parentDocumentId matches the true parent of documentId
        boolean doesFileParentMatch = false;
        File fileParent = file.getParentFile();

        if (fileParent == null || fileParent.equals(parent)) {
            doesFileParentMatch = true;
        }

        // Remove the file if parent matches or file and parent are equal
        if (parent.equals(file) || doesFileParentMatch) {
            if (file.delete()) {
                Log.i(TAG, "Deleted file with id " + documentId);
            } else {
                throw new FileNotFoundException("Failed to delete document with id " + documentId);
            }
        } else {
            throw new FileNotFoundException("Failed to delete document with id " + documentId);
        }
    }
    // END_INCLUDE(remove_document)

    /**
     * overload copyDocument to insist that the parent matches
     */
    public String copyDocument(String sourceDocumentId, String sourceParentDocumentId,
                               String targetParentDocumentId) throws FileNotFoundException {
        Log.v(TAG, "copyDocument with document parent");
        if (!isChildDocument(sourceParentDocumentId, sourceDocumentId)) {
            throw new FileNotFoundException("Failed to copy document with id " +
                    sourceDocumentId + ". Parent is not: " + sourceParentDocumentId);
        }
        return copyDocument(sourceDocumentId, targetParentDocumentId);
    }

    // BEGIN_INCLUDE(copyDocument)
    @Override
    public String copyDocument(String sourceDocumentId, String targetParentDocumentId)
            throws FileNotFoundException {
        Log.v(TAG, "copyDocument");

        File parent = getFileForDocId(targetParentDocumentId);
        File oldFile = getFileForDocId(sourceDocumentId);
        File newFile = new File(parent.getPath(), oldFile.getName());
        try {
            int conflictId = 1;
            while(newFile.exists()) {
                newFile = new File(parent.getPath(), oldFile.getName() + "(" + conflictId++ + ")");
            }
            // Create the new File to copy into
            boolean wasNewFileCreated = false;
            boolean isDirectory = Document.MIME_TYPE_DIR.equals(getTypeForFile(oldFile));
            if(isDirectory) {
                if (newFile.mkdir()) {
                    if (newFile.setWritable(true) && newFile.setReadable(true)) {
                        wasNewFileCreated = true;
                    }
                }
            } else {
                if (newFile.createNewFile()) {
                    if (newFile.setWritable(true) && newFile.setReadable(true)) {
                        wasNewFileCreated = true;
                    }
                }
            }

            if (!wasNewFileCreated) {
                throw new FileNotFoundException("Failed to copy document " + sourceDocumentId +
                        ". Could not create new file.");
            }

            if(!isDirectory) {
                // Copy the bytes into the new file
                try (InputStream inStream = new FileInputStream(oldFile)) {
                    try (OutputStream outStream = new FileOutputStream(newFile)) {
                        // Transfer bytes from in to out
                        byte[] buf = new byte[4096]; // ideal range for network: 2-8k, disk: 8-64k
                        int len;
                        while ((len = inStream.read(buf)) > 0) {
                            outStream.write(buf, 0, len);
                        }
                    }
                }
            }
        } catch (IOException e) {
            throw new FileNotFoundException("Failed to copy document: " + sourceDocumentId +
                    ". " + e.getMessage());
        }
        return getDocIdForFile(newFile);
    }
    // END_INCLUDE(copyDocument)

    // BEGIN_INCLUDE(moveDocument)
    @Override
    public String moveDocument(String sourceDocumentId, String sourceParentDocumentId,
                               String targetParentDocumentId) throws FileNotFoundException {
        Log.v(TAG, "moveDocument");
        try {
            // Copy document, insisting that the parent is correct
            String newDocumentId = copyDocument(sourceDocumentId, sourceParentDocumentId,
                    targetParentDocumentId);
            // Remove old document
            removeDocument(sourceDocumentId, sourceParentDocumentId);
            return newDocumentId;
        } catch (FileNotFoundException e) {
            throw new FileNotFoundException("Failed to move document " + sourceDocumentId);
        }
    }
    // END_INCLUDE(moveDocument)


    @Override
    public String getDocumentType(String documentId) throws FileNotFoundException {
        File file = getFileForDocId(documentId);
        return getTypeForFile(file);
    }

    /**
     * @param projection the requested root column projection
     * @return either the requested root column projection, or the default projection if the
     * requested projection is null.
     */
    private static String[] resolveRootProjection(String[] projection) {
        return projection != null ? projection : DEFAULT_ROOT_PROJECTION;
    }

    private static String[] resolveDocumentProjection(String[] projection) {
        return projection != null ? projection : DEFAULT_DOCUMENT_PROJECTION;
    }

    /**
     * Get a file's MIME type
     *
     * @param file the File object whose type we want
     * @return the MIME type of the file
     */
    private static String getTypeForFile(File file) {
        if (file.isDirectory()) {
            return Document.MIME_TYPE_DIR;
        } else {
            return getTypeForName(file.getName());
        }
    }

    /**
     * Get the MIME data type of a document, given its filename.
     *
     * @param name the filename of the document
     * @return the MIME data type of a document
     */
    private static String getTypeForName(String name) {
        final int lastDot = name.lastIndexOf('.');
        if (lastDot >= 0) {
            final String extension = name.substring(lastDot + 1);
            final String mime = MimeTypeMap.getSingleton().getMimeTypeFromExtension(extension);
            if (mime != null) {
                return mime;
            }
        }
        return "application/octet-stream";
    }

    /**
     * Gets a string of unique MIME data types a directory supports, separated by newlines.  This
     * should not change.
     *
     * @param parent the File for the parent directory
     * @return a string of the unique MIME data types the parent directory supports
     */
    private String getChildMimeTypes(File parent) {
        Set<String> mimeTypes = new HashSet<String>();
        mimeTypes.add("image/*");
        mimeTypes.add("text/*");
        mimeTypes.add("application/vnd.openxmlformats-officedocument.wordprocessingml.document");

        // Flatten the list into a string and insert newlines between the MIME type strings.
        StringBuilder mimeTypesString = new StringBuilder();
        for (String mimeType : mimeTypes) {
            mimeTypesString.append(mimeType).append("\n");
        }

        return mimeTypesString.toString();
    }

    /**
     * Get the document ID given a File.  The document id must be consistent across time.  Other
     * applications may save the ID and use it to reference documents later.
     * <p/>
     * This implementation is specific to this demo.  It assumes only one root and is built
     * directly from the file structure.  However, it is possible for a document to be a child of
     * multiple directories (for example "android" and "images"), in which case the file must have
     * the same consistent, unique document ID in both cases.
     *
     * @param file the File whose document ID you want
     * @return the corresponding document ID
     */
    private String getDocIdForFile(File file) {
        String path = file.getAbsolutePath();

        // Start at first char of path under root
        final String rootPath = mBaseDir.getPath();
        if (rootPath.equals(path)) {
            path = "";
        } else if (rootPath.endsWith("/")) {
            path = path.substring(rootPath.length());
        } else {
            path = path.substring(rootPath.length() + 1);
        }

        return ROOT + ':' + path;
    }

    /**
     * Add a representation of a file to a cursor.
     *
     * @param result the cursor to modify
     * @param docId  the document ID representing the desired file (may be null if given file)
     * @param file   the File object representing the desired file (may be null if given docID)
     * @throws FileNotFoundException
     */
    private void includeFile(MatrixCursor result, String docId, File file)
            throws FileNotFoundException {
        if (docId == null) {
            docId = getDocIdForFile(file);
        } else {
            file = getFileForDocId(docId);
        }

        int flags = 0;

        if (file.isDirectory()) {
            // Request the folder to lay out as a grid rather than a list. This also allows a larger
            // thumbnail to be displayed for each image.
            //            flags |= Document.FLAG_DIR_PREFERS_GRID;

            // Add FLAG_DIR_SUPPORTS_CREATE if the file is a writable directory.
            if (file.isDirectory() && file.canWrite()) {
                flags |= Document.FLAG_DIR_SUPPORTS_CREATE;
            }
        } else if (file.canWrite()) {
            // If the file is writable set FLAG_SUPPORTS_WRITE and
            // FLAG_SUPPORTS_DELETE
            flags |= Document.FLAG_SUPPORTS_WRITE;
            flags |= Document.FLAG_SUPPORTS_DELETE;

            // Add SDK specific flags if appropriate
            if (SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
                flags |= Document.FLAG_SUPPORTS_RENAME;
            }
            if (SDK_INT >= Build.VERSION_CODES.N) {
                flags |= Document.FLAG_SUPPORTS_REMOVE;
                flags |= Document.FLAG_SUPPORTS_MOVE;
                flags |= Document.FLAG_SUPPORTS_COPY;
            }
        }

        final String displayName = file.getName();
        final String mimeType = getTypeForFile(file);

        if (mimeType.startsWith("image/")) {
            // Allow the image to be represented by a thumbnail rather than an icon
            flags |= Document.FLAG_SUPPORTS_THUMBNAIL;
        }

        final MatrixCursor.RowBuilder row = result.newRow();
        row.add(Document.COLUMN_DOCUMENT_ID, docId);
        if(file.getAbsolutePath() == mBaseDir.getAbsolutePath()) {
            row.add(Document.COLUMN_DISPLAY_NAME, getContext().getApplicationInfo().loadLabel(getContext().getPackageManager()).toString());
        } else {
            row.add(Document.COLUMN_DISPLAY_NAME, displayName);
        }
        row.add(Document.COLUMN_SIZE, file.length());
        row.add(Document.COLUMN_MIME_TYPE, mimeType);
        row.add(Document.COLUMN_LAST_MODIFIED, file.lastModified());
        row.add(Document.COLUMN_FLAGS, flags);

        // Add a custom icon
        row.add(Document.COLUMN_ICON, R.drawable.love);
    }

    /**
     * Translate your custom URI scheme into a File object.
     *
     * @param docId the document ID representing the desired file
     * @return a File represented by the given document ID
     * @throws java.io.FileNotFoundException
     */
    private File getFileForDocId(String docId) throws FileNotFoundException {
        File target = mBaseDir;
        if (docId.equals(ROOT)) {
            return target;
        }
        final int splitIndex = docId.indexOf(':', 1);
        if (splitIndex < 0) {
            throw new FileNotFoundException("Missing root for " + docId);
        } else {
            final String path = docId.substring(splitIndex + 1);
            target = new File(target, path);
            if (!target.exists()) {
                throw new FileNotFoundException("Missing file for " + docId + " at " + target);
            }
            return target;
        }
    }
}