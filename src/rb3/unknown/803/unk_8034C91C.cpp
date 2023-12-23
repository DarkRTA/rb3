#include "filepath.hpp"
#include "string.hpp"
#include "unknown.hpp"

extern char lbl_80856E78[];
extern char *FileMakePath(char *, char *, int);

// fn_8034C91C
void FilePath::Set(const char *a, const char *b) {
    if (b != nullptr && *b != '\0') {
        String::operator=(FileMakePath((char *)a, (char *)b, 0));
        return;
    } else
        String::operator=(lbl_80856E78);
}