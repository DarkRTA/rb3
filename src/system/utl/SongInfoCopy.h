#ifndef UTL_SONGINFOCOPY_H
#define UTL_SONGINFOCOPY_H
#include "utl/Symbol.h"
#include "utl/Str.h"
#include "utl/SongInfoAudioType.h"

class SongInfoCopy {
public:
    SongInfoCopy();
    virtual ~SongInfoCopy();
    virtual const char* GetName() const;
    virtual const char* GetBaseFileName() const;
    virtual const char* GetPackageName() const;
    // TODO: fix the return types of these methods below as you implement them
    virtual int GetTracks() const;
    virtual bool IsPlayTrackChannel(int) const;
    virtual int FindTrackChannel(SongInfoAudioType) const;
    virtual int NumChannelsOfTrack(SongInfoAudioType) const;
    virtual int TrackIndex(SongInfoAudioType) const;
    virtual int GetNumVocalParts() const;
    virtual int GetHopoThreshold() const;
    // TODO: there are also more virtual methods in the vtable, declare and define them

    Symbol sym;
    String str1;
    String str2;
};

#endif
