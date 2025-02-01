#include "world/LightHue.h"
#include "math/Color.h"
#include "rndobj/Bitmap.h"
#include "utl/BufStream.h"
#include "utl/Loader.h"
#include "utl/MemMgr.h"
#include "utl/Symbols.h"

INIT_REVS(LightHue)

LightHue::LightHue() : mLoader(0), mPath(), mKeys() {}

LightHue::~LightHue() { delete mLoader; }

BEGIN_COPYS(LightHue)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(LightHue)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mPath)
        COPY_MEMBER(mKeys)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(LightHue, 0x27)

BEGIN_LOADS(LightHue)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void LightHue::PreLoad(BinStream &bs) {
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mPath;
    if (bs.Cached()) {
        bs >> mKeys;
    } else if (!mPath.empty()) {
        mLoader = new FileLoader(mPath, mPath.c_str(), kLoadFront, 0, false, true, 0);
    }
}

void LightHue::PostLoad(BinStream &bs) {
    if (!bs.Cached())
        Sync();
}

// matches in retail
void LightHue::Sync() {
    mKeys.clear();
    if (!mPath.empty()) {
        if (!mLoader) {
            mLoader =
                new FileLoader(mPath, mPath.c_str(), kLoadFront, 0, false, true, nullptr);
        }
        TheLoadMgr.PollUntilLoaded(mLoader, nullptr);
        int ibuf;
        void *buffer = (void *)mLoader->GetBuffer(&ibuf);
        RELEASE(mLoader);
        if (buffer) {
            RndBitmap bmap;
            BufStream bs(buffer, ibuf, true);
            if (bmap.LoadBmp(&bs)) {
                mKeys.resize(bmap.Width());
                for (int i = 0; i < bmap.Width(); i++) {
                    unsigned char r, g, b, a;
                    bmap.PixelColor(i, 0, r, g, b, a);
                    float h, s, l;
                    MakeHSL(
                        Hmx::Color(
                            (float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f
                        ),
                        h,
                        s,
                        l
                    );
                    Key<Vector3> &curKey = mKeys[i];
                    curKey.frame = (float)i / (float)bmap.Width();
                    float &x = mKeys[i].value.x;
                    x = h;
                    float &y = mKeys[i].value.y;
                    y = s;
                    float &z = mKeys[i].value.z;
                    z = l;
                }
            }
            _MemFree(buffer);
        }
    }
}

// matches in retail
void LightHue::TranslateColor(const Hmx::Color &col, Hmx::Color &res) {
    if (!mKeys.empty()) {
        float maxcol = Max(1.0f, Max(col.red, col.green, col.blue));
        Hmx::Color col30;
        Multiply(col, 1.0f / maxcol, col30);
        float h, s, l;
        MakeHSL(col30, h, s, l);
        Vector3 vec;
        mKeys.AtFrame(h, vec);
        float clamped = Clamp(0.0f, 1.0f, l * vec.z * 2.0f);
        MakeColor(vec.x, s * vec.y, clamped, res);
        Multiply(res, maxcol, res);
    } else
        res = col;
}

BEGIN_HANDLERS(LightHue)
    HANDLE(save_default, OnSaveDefault)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x97)
END_HANDLERS

DataNode LightHue::OnSaveDefault(DataArray *da) {
    RndBitmap bmap;
    bmap.Create(0x100, 8, 0, 0x18, 0, 0, 0, 0);
    for (int i = 0; i < 0x100; i++) {
        Hmx::Color color;
        MakeColor((float)i / 255.0f, 1.0f, 0.5f, color);
        unsigned char red = color.red * 255.0f;
        unsigned char green = color.green * 255.0f;
        unsigned char blue = color.blue * 255.0f;
        int j = 0;
        for (; j < 8; j++) {
            bmap.SetPixelColor(i, j, red, green, blue, 0xff);
        }
    }
    bmap.SaveBmp(da->Str(2));
    return 0;
}

BEGIN_PROPSYNCS(LightHue)
    SYNC_PROP_MODIFY_ALT(path, mPath, Sync())
END_PROPSYNCS