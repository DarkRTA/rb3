#include "game/ChordPreview.h"
#include "decomp.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "utl/Symbol.h"

DECOMP_FORCEACTIVE(
    ChordPreview, "sound", "song_select", "fade_time", __FILE__, "contentName"
)

DECOMP_FORCEBLOCK(ChordPreview, (void), Hmx::Object::New<Fader>(); new ContentMgr::Callback;)

void ForceContentMgrCBDtor(ContentMgr::Callback *cb) { delete cb; }

void ChordPreview::Start(Symbol s) {
    MILO_ASSERT(mGuitarFader && mSilenceFader, 0x65);
    if (s == mSong)
        return;
    if (!s.Null()) {
        if (!TheSongMgr.HasSong(s, true))
            return;
        BandSongMetadata *data =
            (BandSongMetadata *)TheSongMgr.Data(TheSongMgr.GetSongIDFromShortName(s, true)
            );
        if (data && !data->IsVersionOK()) {
            s = gNullStr;
        }
        if (!mRegisteredWithCM) {
            TheContentMgr->RegisterCallback(this, false);
            mRegisteredWithCM = true;
        }
    }
    mSong = s;
    mGuitarFader->SetVal(0);
    for (int i = 0; i < 3; i++) {
        StreamData &data = mStreamData[i];
        MILO_ASSERT(data.fader, 0x84);
        switch (data.state) {
        case 0:
        case 1:
            data.Reset(false);
            break;
        case 2:
            data.state = 3;
            break;
        case 5:
            data.fader->DoFade(-48.0f, mFadeMs);
            data.state = 7;
            break;
        default:
            break;
        }
    }
}

DECOMP_FORCEACTIVE(ChordPreview, "play stream %d\n", "no stream available to play\n")

bool ForceContentMgrMountContentFunc(ContentMgr *mgr, Stream *s) {
    mgr->MountContent(gNullStr);
    return s->IsPaused();
}

void ChordPreview::StreamData::Reset(bool b1) {
    RELEASE(stream);
    state = 0;
    if (b1) {
        RELEASE(fader);
    }
}

void ForceRemainingContentMgrCBVFuncs(ContentMgr::Callback *cb) {
    cb->HasContentAltDirs();
    cb->ContentAltDirs();
    cb->ContentPattern();
    cb->ContentCancelled();
    cb->ContentDone();
    cb->ContentLoaded(0, (ContentLocT)0, gNullStr);
    cb->ContentUnmounted(0);
    cb->ContentAllMounted();
    cb->ContentMountBegun(0);
    cb->ContentDiscovered(gNullStr);
    cb->ContentStarted();
    cb->ContentDir();
    cb->ContentFailed(0);
    cb->ContentMounted(0, 0);
}