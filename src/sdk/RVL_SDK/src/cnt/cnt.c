#include "revolution/cnt/cnt.h"
#include <revolution/CNT.h>

BOOL CNTOpenDir(CNTHandle *handle, const char *path, CNTDir *dir) {
    switch (handle->type) {
    case ARC:
        return ARCOpenDir(&handle->arc, path, &dir->arc);
    case DVD:

    default:
        return FALSE;
    }
}

BOOL CNTReadDir(CNTDir *dir, CNTDirEntry *entry) {
    switch (dir->type) {
    case ARC:
        entry->type = ARC;
        return ARCReadDir(&dir->arc, &entry->arc);
    case DVD:
        entry->type = DVD;
        entry->pad = 0;
        return DVDReadDir(&dir->dvd, &entry->dvd);
    default:
        return FALSE;
    }
}

BOOL CNTCloseDir(CNTDir *dir) {
    switch (dir->type) {
    case ARC:
        return ARCCloseDir(&dir->arc);
    case DVD:
        return DVDCloseDir(&dir->dvd);
    default:
        return FALSE;
    }
}
