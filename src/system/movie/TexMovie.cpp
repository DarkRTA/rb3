#include "TexMovie.h"
#include "decomp.h"
#include "movie/Movie.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"
#include "os/File.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Rnd.h"
#include "rndobj/Utl.h"
#include "utl/FilePath.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"
#include <cstddef>

INIT_REVS(TexMovie)

TexMovie::TexMovie() : mTex(this, NULL), mLoop(1), unk_0x35(0), mFillWidth(0), mMovie() {}

TexMovie::~TexMovie() { mMovie.End(); }

BEGIN_COPYS(TexMovie)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    COPY_SUPERCLASS(RndPollable)
    CREATE_COPY(TexMovie)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTex)
        COPY_MEMBER(mLoop)
        COPY_MEMBER(unk_0x38)
        COPY_MEMBER(mFillWidth)
    END_COPYING_MEMBERS
END_COPYS

void TexMovie::Replace(Hmx::Object* a, Hmx::Object* b) {
    Hmx::Object::Replace(a, b);
    if (mTex == a) {
        mMovie.End();
        mTex = dynamic_cast<RndTex*>(b);
    }
}

SAVE_OBJ(TexMovie, 61)

BEGIN_LOADS(TexMovie) // retail matches, still some clownery afoot
    LOAD_REVS(bs)
    ASSERT_REVS(5, 1)
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    RndPollable::Load(bs);
    
    if (gAltRev != 0) bs >> mFillWidth;
    bs >> mTex >> mLoop;
    if (gRev < 4) {
        u8 ccc; bs >> ccc;
    }
    bs >> unk_0x38;
    DataNode dn = HandleType(change_file_msg);
    if (dn.Type() == kDataString) {
        unk_0x38.SetRoot(dn.Str(NULL));
    }
    if (gRev > 1 && gRev < 3) {
        u8 ccc; bs >> ccc;
    }
    FilePathTracker tracker(".");
    BeginMovie(gRev > 4 ? &bs : NULL);
END_LOADS

void TexMovie::BeginMovie(BinStream* bs) {
    mMovie.End();
    if (!unk_0x38.empty()) {
        if (mTex) {
            MILO_ASSERT(mTex->IsRenderTarget(), 124);
            int y = mTex->mHeight;
            mMovie.SetWidthHeight(mTex->mWidth, y);
        }
        mMovie.Begin(FileRelativePath(FileRoot(), unk_0x38.c_str()), 0, 0, mLoop, 1, mFillWidth, 0, bs);
    }
}

void TexMovie::DrawToTexture() {
    if (!unk_0x38.empty() && mTex && mMovie.Ready() && mMovie.IsOpen()) {
        mTex->MakeDrawTarget();
        mMovie.Draw();
        mTex->FinishDrawTarget();
        TheRnd->MakeDrawTarget();
    }
}

void TexMovie::DrawShowing() {
    if (mTex) return;
    mMovie.Draw();
}

void TexMovie::DrawPreClear() {
    if (TheRnd->unk_0xE4 != 4 && mShowing) DrawToTexture();
}

void TexMovie::Poll() {
    if (TheRnd->unk_0xE4 != 4) {
        if (mShowing) {
            mMovie.SetPaused(false);
            if(!mMovie.Poll())
            mMovie.End();
        } else mMovie.SetPaused(true);
    }
}

void TexMovie::Enter() {
    unk_0x35 = true;
    RndPollable::Enter();
    if (mTex) {
        mTex->MakeDrawTarget();
        Hmx::Rect r(0,0,1,1); Hmx::Color c(0,0,0,1);
        TheRnd->DrawRectScreen(r,c, NULL, NULL, NULL);
        mTex->FinishDrawTarget();
        TheRnd->MakeDrawTarget();
    }
    mMovie.CheckOpen(false);
    UpdatePreClearState();
}

void TexMovie::Exit() {
    unk_0x35 = false;
    RndPollable::Exit();
}

void TexMovie::SetFile(const FilePath& fp) {
    mMovie.End();
    unk_0x38 = fp;
    BeginMovie(NULL);
}

void TexMovie::UpdatePreClearState() {
    if (unk_0x35) TheRnd->PreClearDrawAddOrRemove(this, mTex, TheRnd->Unk130());
}

DataNode TexMovie::OnGetRenderTextures(DataArray*) {
    return GetRenderTextures(mDir);
}

DataNode TexMovie::OnPlayMovie(DataArray* da) {
    if (da->Int(2)) {
        if (!mMovie.IsLoading() && !mMovie.IsOpen()) BeginMovie(NULL);
    } else mMovie.End();
    return DataNode();
}

BEGIN_HANDLERS(TexMovie)
    HANDLE(get_render_textures, OnGetRenderTextures)
    HANDLE(play_movie, OnPlayMovie)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(265)
END_HANDLERS

BEGIN_PROPSYNCS(TexMovie)
    SYNC_PROP_MODIFY_ALT(output_texture, mTex, BeginMovie(NULL))
    if (sym == bink_movie_file) {
        if (_op == kPropSet) {
            FilePath fp(_val.Str(NULL));
            SetFile(fp);
        } else {
            if (_op == kPropUnknown0x40) return false;
            _val = FileRelativePath(FilePath::sRoot.c_str(), unk_0x38.c_str());
        }
        return true;
    }
    SYNC_PROP(loop, mLoop)
    SYNC_PROP(fill_width, mFillWidth)
    SYNC_SUPERCLASS(RndDrawable)
    SYNC_SUPERCLASS(RndPollable)
END_PROPSYNCS
