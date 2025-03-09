#include "Movie.h"
#include "os/Timer.h"
#include "rndobj/Tex.h"
#include "rndwii/Tex.h"

WiiMovie::WiiMovie() : unk_0x40(0), unk_0x48(0) {}

WiiMovie::~WiiMovie() {}

void WiiMovie::SetFile(const FilePath &fp, bool b) {}

void WiiMovie::SetTex(RndTex *tex) {
    RndMovie::SetTex(tex);
    if (mTex == nullptr)
        return;
    int x = mVideoData.mMagic, y;
    if (x == 0 || (y = mVideoData.mWidth) == 0 || mVideoData.mHeight == 0) {
        mTex->SetBitmap(16, 16, 32, RndTex::kRegular, 0, NULL);
    } else {
        mTex->SetBitmap(
            x, y, const_cast<const SIVideo &>(mVideoData).Bpp(), RndTex::kMovie, 0, NULL
        );
    }
}

void WiiMovie::SetFrame(float frame, float blend) {
    START_AUTO_TIMER("movie");

    Update();
}

void WiiMovie::Update() {
    WiiTex *tex = (WiiTex *)(RndTex *)mTex;
    memcpy(tex->GetMovieLoadingFramePtr(), unk_0x54, mVideoData.FrameSize());
    tex->MovieSwapFrames();
}

void WiiMovie::StreamReadFinish() {}

void WiiMovie::StreamNextBuffer() { StreamReadFinish(); }

void WiiMovie::StreamRestart(int i) {
    StreamReadFinish();
    StreamNextBuffer();
}
