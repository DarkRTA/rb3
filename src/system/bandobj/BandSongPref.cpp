#include "bandobj/BandSongPref.h"
#include "obj/Object.h"
#include "utl/Symbols.h"

INIT_REVS(BandSongPref)

BandSongPref::BandSongPref()
    : mPart2Instrument("guitar"), mPart3Instrument("bass"), mPart4Instrument("drum"),
      mAnimGenre("rocker") {}

SAVE_OBJ(BandSongPref, 24)

BEGIN_LOADS(BandSongPref)
    LOAD_REVS(bs)
    ASSERT_REVS(3, 0)
    LOAD_SUPERCLASS(Hmx::Object);
    bs >> mPart2Instrument;
    bs >> mPart3Instrument;
    bs >> mPart4Instrument;
    if (gRev != 0 && gRev < 3) {
        u8 dump;
        bs >> dump;
    }
    if (gRev > 1)
        bs >> mAnimGenre;
END_LOADS

BEGIN_COPYS(BandSongPref)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(BandSongPref)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPart2Instrument)
        COPY_MEMBER(mPart3Instrument)
        COPY_MEMBER(mPart4Instrument)
        COPY_MEMBER(mAnimGenre)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(BandSongPref)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(70)
END_HANDLERS

BEGIN_PROPSYNCS(BandSongPref)
    SYNC_PROP(part2_inst, mPart2Instrument)
    SYNC_PROP(part3_inst, mPart3Instrument)
    SYNC_PROP(part4_inst, mPart4Instrument)
    SYNC_PROP(animation_genre, mAnimGenre)
END_PROPSYNCS
