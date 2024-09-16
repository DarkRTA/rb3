#include "bandobj/LayerDir.h"
#include "rndobj/Cam.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(LayerDir)

RndCam* LayerDir::sCam;
LayerDir* gLayerDirOwner;

void LayerDir::Init(){
    sCam = Hmx::Object::New<RndCam>();
    sCam->SetFrustum(0.01f, 5.0f, 0.0f, 1.0f);
    Register();
}

LayerDir::LayerDir() : mLayers(this), mUseFreeCam(0) {
    
}

void LayerDir::DrawShowing(){
    if(!mUseFreeCam) sCam->Select();
    RndDir::DrawShowing();
}

RndCam* LayerDir::CamOverride(){
    return mUseFreeCam ? 0 : sCam;
}

BinStream& operator>>(BinStream& bs, LayerDir::Layer& layer){
    bs >> layer.mName;
    layer.mMat.Load(bs, false, 0);
    bs >> layer.mActive;
    bs >> layer.mColor;
    if(LayerDir::gRev > 3) bs >> layer.mColorPalette;
    bs >> layer.mAlpha;
    bs >> layer.mBitmap;
    bs >> layer.mLayerOptional;
    bs >> layer.mAllowColor;
    bs >> layer.mAllowAlpha;
    bs >> layer.mAlphaMin;
    bs >> layer.mAlphaMax;
    bs >> layer.mBitmapList;
    if(LayerDir::gRev == 1){ bool b; bs >> b; }
    if(LayerDir::gRev > 1) layer.mProxy.Load(bs, false, 0);
    if(LayerDir::gRev > 6) bs >> layer.mColorIdx;
    return bs;
}

SAVE_OBJ(LayerDir, 0xC3)

void LayerDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(7, 0);
    if(gRev < 5) bs >> mLayers;
    if(gRev != 0) bs >> mUseFreeCam;
    PushRev(packRevs(gAltRev, gRev), this);
    RndDir::PreLoad(bs);
}

void LayerDir::PostLoad(BinStream& bs){
    RndDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev == 5) bs >> mLayers;
    if(gRev > 5 && !IsProxy()) bs >> mLayers;
}

BEGIN_COPYS(LayerDir)
    COPY_SUPERCLASS(RndDir)
    CREATE_COPY(LayerDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mUseFreeCam)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_CUSTOM_PROPSYNC(LayerDir::Layer)
    SYNC_PROP(name, o.mName)
    SYNC_PROP_MODIFY_ALT(mat, o.mMat, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP_MODIFY_ALT(bitmap, o.mBitmap, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP_MODIFY_ALT(active, o.mActive, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP_MODIFY_ALT(color, o.mColor, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP_MODIFY_ALT(color_idx, o.mColorIdx, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP_MODIFY_ALT(alpha, o.mAlpha, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP_MODIFY_ALT(proxy, o.mProxy, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP(layer_optional, o.mLayerOptional)
    SYNC_PROP(allow_color, o.mAllowColor)
    SYNC_PROP_MODIFY_ALT(color_palette, o.mColorPalette, gLayerDirOwner->RefreshLayer(o, false))
    SYNC_PROP(allow_alpha, o.mAllowAlpha)
    SYNC_PROP(alpha_min, o.mAlphaMin)
    SYNC_PROP(alpha_max, o.mAlphaMax)
    SYNC_PROP(bitmap_list, o.mBitmapList)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(LayerDir)
    gLayerDirOwner = this;
    SYNC_SUPERCLASS(RndDir)
    SYNC_PROP(layers, mLayers)
    SYNC_PROP(use_free_cam, mUseFreeCam)
END_PROPSYNCS

BEGIN_HANDLERS(LayerDir)
    HANDLE_SUPERCLASS(RndDir)
    HANDLE(get_bitmap_list, GetBitmapList)
    HANDLE(randomize_colors, RandomizeColors)
    HANDLE_CHECK(0x12E)
END_HANDLERS