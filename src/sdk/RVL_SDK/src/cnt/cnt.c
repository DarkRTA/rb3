#include "revolution/cnt/cnt.h"
#include <revolution/CNT.h>

BOOL CNTOpenDir(CNTHandle *handle, const char *path, CNTDir *dir) {
    BOOL ret;
    switch (handle->type) {
    case ARC:
        dir->type = 1;
        ret = ARCOpenDir(&handle->nand.ArcHandle, path, &dir->arc);
        break;
    case DVD:
        ret = FALSE;
        dir->type = 2;
        dir->pad = 0;
        int entrynum = contentConvertPathToEntrynumDVD(path);
        if (entrynum >= 0) {
            ret = DVDFastOpenDir(entrynum, &dir->dvd);
        }
        break;
    default:
        ret = FALSE;
        break;
    }
    return ret;
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
