#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Function to rename a file
int rename_file(const char *old_path,const char *new_path) {
#ifdef _WIN32
    // Windows uses MoveFile for renaming
    return MoveFile(old_path, new_path) ? 0 : -1;
#else
    // Linux uses rename
    return rename(old_path, new_path);
#endif
}