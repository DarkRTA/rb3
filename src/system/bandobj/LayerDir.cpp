#include "bandobj/LayerDir.h"
#include "utl/Symbols.h"

LayerDir* gLayerDirOwner;

LayerDir::LayerDir() : mLayers(this), mUseFreeCam(0) {
    
}

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