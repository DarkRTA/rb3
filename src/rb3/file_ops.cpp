#include "file_ops.hpp"
#include "std/string.h"

char lbl_809071C8[0x100];

// fn_802FA848
char *FileGetPath(char *arg1, char *arg2) {
    char *p2;
    if (arg2 == 0)
        arg2 = lbl_809071C8;
    if (arg1 != 0) {
        strcpy(arg2, arg1);
        p2 = arg2 + strlen(arg2);
        p2--;
        while (p2 >= arg2 && *p2 != '/' && *p2 != '\\') {
            p2--;
        }
        if (p2 >= arg2) {
            if ((p2 == arg2) || (p2[-1] == ':'))
                p2[1] = '\0';
            else
                *p2 = '\0';
            return arg2;
        }
    }
    *arg2 = '.';
    arg2[1] = '\0';
    return arg2;
}

// fn_802FA918
char *FileGetExt(char *filename) {
    char *end = filename + strlen(filename);
    for (char *search = end - 1; search >= filename; search--) {
        if (*search == '.') {
            return search + 1;
        } else if (*search == '/' || *search == '\\') {
            return end;
        }
    }
    return end;
}

char lbl_809072C8[0x100];

// fn_802FA994
char *FileGetDrive(char *c) {
    char *p1 = strchr(c, ':');
    if (p1 != 0) {
        strncpy(lbl_809072C8, c, p1 - c);
        lbl_809072C8[p1 - c] = '\0';
    } else
        lbl_809072C8[0] = '\0';
    return lbl_809072C8;
}

char lbl_809073C8[0x100];

// fn_802FAA10
char *FileGetBase(char *fname, char *base) {
    char *ext;
    char *dir;

    if (base == 0)
        base = lbl_809073C8;
    dir = strrchr(fname, '/');
    if ((dir != 0) || (dir = strrchr(fname, '\\'), (dir != 0))) {
        strcpy(base, dir + 1);
    } else
        strcpy(base, fname);

    ext = strrchr(base, '.');
    if (ext != 0) {
        *ext = 0;
    }
    return base;
}

char lbl_809074C8[0x100];

// fn_802FAAC0
char *FileGetName(char *arg) {
    char *dir = strrchr(arg, '/');
    if ((dir != 0) || (dir = strrchr(arg, '\\'), (dir != 0))) {
        strcpy(lbl_809074C8, dir + 1);
    } else
        strcpy(lbl_809074C8, arg);
    return lbl_809074C8;
}