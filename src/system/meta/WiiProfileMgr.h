#ifndef META_WIIPROFILEMGR_H
#define META_WIIPROFILEMGR_H

class LocalUser; // forward dec

// TODO: fix header
class WiiProfileMgr {
public:
    int dummy;
    int GetIndexForUser(const LocalUser*) const;
    int GetIdForIndex(int) const;
    bool IsIndexValid(int) const;
    int GetIndexForPad(int) const;
};

extern WiiProfileMgr TheWiiProfileMgr;

#endif
