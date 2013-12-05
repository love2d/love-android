/*
 * APK support routines for PhysicsFS.
 * Based von zip.c.
 *
 * A apk (android) file is just a zip file. But for LÖVE
 * only the assets/ content is necessary and therefore
 * this hides everything outside the assets/ directory
 * (like a chroot into assets/).
 *
 * Please see the file LICENSE.txt in the source's root directory.
 *
 *  This file is heavily based on zip.c by Ryan C. Gordon
 */

#if (defined PHYSFS_SUPPORTS_APK)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32_WCE
#include <errno.h>
#include <time.h>
#endif
#include "physfs.h"
#include "zlib.h"

#define __PHYSICSFS_INTERNAL__
#include "physfs_internal.h"

extern const PHYSFS_ArchiveInfo    __PHYSFS_ArchiveInfo_ZIP;
extern const PHYSFS_Archiver       __PHYSFS_Archiver_ZIP;

static PHYSFS_sint64 APK_read(fvoid *opaque, void *buf,
                              PHYSFS_uint32 objSize, PHYSFS_uint32 objCount)
{
	return __PHYSFS_Archiver_ZIP.read(opaque, buf, objSize, objCount);
} /* APK_read */


static PHYSFS_sint64 APK_write(fvoid *opaque, const void *buf,
                               PHYSFS_uint32 objSize, PHYSFS_uint32 objCount)
{
	return __PHYSFS_Archiver_ZIP.write(opaque, buf, objSize, objCount);
} /* APK_write */


static int APK_eof(fvoid *opaque)
{
	return __PHYSFS_Archiver_ZIP.eof(opaque);
} /* APK_eof */


static PHYSFS_sint64 APK_tell(fvoid *opaque)
{
	return __PHYSFS_Archiver_ZIP.tell(opaque);
} /* APK_tell */


static int APK_seek(fvoid *opaque, PHYSFS_uint64 offset)
{
	return __PHYSFS_Archiver_ZIP.seek(opaque, offset);
} /* APK_seek */


static PHYSFS_sint64 APK_fileLength(fvoid *opaque)
{
    return __PHYSFS_Archiver_ZIP.fileLength(opaque);
} /* APK_fileLength */


static int APK_fileClose(fvoid *opaque)
{
	return __PHYSFS_Archiver_ZIP.fileClose(opaque);
} /* APK_fileClose */



static int APK_isArchive(const char *filename, int forWriting)
{
    int filename_len = 0;

    // does not end with .apk? then ignore this archive
    filename_len = strlen(filename);
    if ((filename_len <= 4) ||
    	(filename[filename_len - 4] != '.') ||
		(filename[filename_len - 3] != 'a' && filename[filename_len - 3] != 'A') ||
		(filename[filename_len - 2] != 'p' && filename[filename_len - 2] != 'P') ||
		(filename[filename_len - 1] != 'k' && filename[filename_len - 1] != 'K'))
    {
    	return 0;
    }
    else
    {
    	return __PHYSFS_Archiver_ZIP.isArchive(filename, forWriting);
    }
} /* APK_isArchive */



static void *APK_openArchive(const char *name, int forWriting)
{
    return __PHYSFS_Archiver_ZIP.openArchive(name, forWriting);
} /* APK_openArchive */


/**
 * Allocates a new string and appends assets/ name.
 * Result must be freed manually with allocator.Free
 * if not necessary anymore
 */
char *append_assets(const char *name)
{
	char *patched_name;
	int name_len = strlen(name);

	patched_name = allocator.Malloc(7 + name_len + 1);

	memcpy(patched_name, "assets/", 7);
	memcpy(patched_name + 7, name, name_len);
	patched_name[7 + name_len + 1 - 1] = 0;

	return patched_name;
}


/**
 * just stores the parameter to an APK_enumerateFiles call to use them
 * in the delegated call to cb
 */
typedef struct APK_originalEnumerateFileCallParameter
{
	dvoid *opaque;
	const char *dname;
	int omitSymLinks;
	PHYSFS_EnumFilesCallback cb;
	const char *origdir;
	void *callbackdata;
} APK_originalEnumerateFileCallParameter;

static void apk_enumerateFilesCallback(void *data, const char *origdir,
                                         const char *fname)
{
	APK_originalEnumerateFileCallParameter *callParameterPtr;

	callParameterPtr = (APK_originalEnumerateFileCallParameter *)data;

	(callParameterPtr->cb)(callParameterPtr->callbackdata, callParameterPtr->origdir, fname);
}

static void APK_enumerateFiles(dvoid *opaque, const char *dname,
                               int omitSymLinks, PHYSFS_EnumFilesCallback cb,
                               const char *origdir, void *callbackdata)
{
	char *patched_dname;
	APK_originalEnumerateFileCallParameter callParameter;

	callParameter.opaque = opaque;
	callParameter.dname = dname;
	callParameter.omitSymLinks = omitSymLinks;
	callParameter.cb = cb;
	callParameter.origdir = origdir;
	callParameter.callbackdata = callbackdata;

	patched_dname = append_assets(dname);

	__PHYSFS_Archiver_ZIP.enumerateFiles(opaque, patched_dname, omitSymLinks, apk_enumerateFilesCallback, origdir, &callParameter);

	allocator.Free(patched_dname);
} /* APK_enumerateFiles */


static int APK_exists(dvoid *opaque, const char *name)
{
	int retval = 0;
	char *patched_name = append_assets(name);

	retval = __PHYSFS_Archiver_ZIP.exists(opaque, patched_name);

	allocator.Free(patched_name);

	return retval;
} /* APK_exists */


static PHYSFS_sint64 APK_getLastModTime(dvoid *opaque,
                                        const char *name,
                                        int *fileExists)
{
	int retval = 0;
	char *patched_name = append_assets(name);

	retval = __PHYSFS_Archiver_ZIP.getLastModTime(opaque, patched_name, fileExists);

	allocator.Free(patched_name);

	return retval;
} /* APK_getLastModTime */


static int APK_isDirectory(dvoid *opaque, const char *name, int *fileExists)
{
	int retval = 0;
	char *patched_name = append_assets(name);

	retval = __PHYSFS_Archiver_ZIP.isDirectory(opaque, patched_name, fileExists);

	allocator.Free(patched_name);

	return retval;
} /* APK_isDirectory */


static int APK_isSymLink(dvoid *opaque, const char *name, int *fileExists)
{
	int retval = 0;
	char *patched_name = append_assets(name);

	retval = __PHYSFS_Archiver_ZIP.isSymLink(opaque, patched_name, fileExists);

	allocator.Free(patched_name);

	return retval;
} /* APK_isSymLink */


static fvoid *APK_openRead(dvoid *opaque, const char *fnm, int *fileExists)
{
	fvoid * retval;
	char *patched_name = append_assets(fnm);

	retval = __PHYSFS_Archiver_ZIP.openRead(opaque, patched_name, fileExists);

	allocator.Free(patched_name);

	return retval;
} /* APK_openRead */


static fvoid *APK_openWrite(dvoid *opaque, const char *filename)
{
    BAIL_MACRO(ERR_NOT_SUPPORTED, NULL);
} /* APK_openWrite */


static fvoid *APK_openAppend(dvoid *opaque, const char *filename)
{
    BAIL_MACRO(ERR_NOT_SUPPORTED, NULL);
} /* APK_openAppend */


static void APK_dirClose(dvoid *opaque)
{
	__PHYSFS_Archiver_ZIP.dirClose(opaque);
} /* APK_dirClose */


static int APK_remove(dvoid *opaque, const char *name)
{
    BAIL_MACRO(ERR_NOT_SUPPORTED, 0);
} /* APK_remove */


static int APK_mkdir(dvoid *opaque, const char *name)
{
    BAIL_MACRO(ERR_NOT_SUPPORTED, 0);
} /* APK_mkdir */


const PHYSFS_ArchiveInfo __PHYSFS_ArchiveInfo_APK =
{
    "APK",
    APK_ARCHIVE_DESCRIPTION,
    "based on __PHYSFS_Archiver_ZIP.ARCHIVE by Ryan C. Gordon <icculus@icculus.org>",
    "http://icculus.org/physfs/",
};


const PHYSFS_Archiver __PHYSFS_Archiver_APK =
{
    &__PHYSFS_ArchiveInfo_APK,
    APK_isArchive,          /* isArchive() method      */
    APK_openArchive,        /* openArchive() method    */
    APK_enumerateFiles,     /* enumerateFiles() method */
    APK_exists,             /* exists() method         */
    APK_isDirectory,        /* isDirectory() method    */
    APK_isSymLink,          /* isSymLink() method      */
    APK_getLastModTime,     /* getLastModTime() method */
    APK_openRead,           /* openRead() method       */
    APK_openWrite,          /* openWrite() method      */
    APK_openAppend,         /* openAppend() method     */
    APK_remove,             /* remove() method         */
    APK_mkdir,              /* mkdir() method          */
    APK_dirClose,           /* dirClose() method       */
    APK_read,               /* read() method           */
    APK_write,              /* write() method          */
    APK_eof,                /* eof() method            */
    APK_tell,               /* tell() method           */
    APK_seek,               /* seek() method           */
    APK_fileLength,         /* fileLength() method     */
    APK_fileClose           /* fileClose() method      */
};

#endif  /* defined PHYSFS_SUPPORTS_APK */

/* end of apk.c ... */

