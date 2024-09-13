#include "bandobj/OutfitConfig.h"
#include "utl/Symbols.h"

OutfitConfig* gOutfitConfigOwner;

OutfitConfig::OutfitConfig() : mMats(this), unk38(0), unk3c(0), mComputeAO(1), mPatches(this), mPermaProject(0), mPiercings(this),
    mTexBlender(this, 0), mWrinkleBlender(this, 0), mOverlays(this), mBandLogo(this, 0) {
    for(int i = 0; i < 3; i++) mColors[i] = i;
}

BEGIN_HANDLERS(OutfitConfig)
    HANDLE_ACTION(recompose, Recompose())
    HANDLE_ACTION(randomize_colors, Randomize())
    HANDLE_EXPR(num_color_options, NumColorOptions())
    HANDLE_ACTION(compress_textures, CompressTextures())
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xB3C)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(OutfitConfig::Piercing::Piece)
    SYNC_PROP(attachment, o.mAttachment)
    SYNC_PROP(highlight, o.mHighlight)
    SYNC_PROP(vert, o.mVert)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(OutfitConfig::Piercing)
    SYNC_PROP(piercing, o.mPiercing)
    SYNC_PROP(reskin, o.mReskin)
    SYNC_PROP(pieces, o.mPieces)
END_CUSTOM_PROPSYNC

void PropSyncTwoColor(OutfitConfig::MatSwap& swap){
    swap.SyncTwoColor();
    gOutfitConfigOwner->Recompose();
}

BEGIN_CUSTOM_PROPSYNC(OutfitConfig::MatSwap)
    SYNC_PROP_MODIFY_ALT(mat, o.mMat, gOutfitConfigOwner->Recompose())
    SYNC_PROP_MODIFY_ALT(resource_mat, o.mResourceMat, gOutfitConfigOwner->Recompose())
    SYNC_PROP_MODIFY_ALT(two_color_diffuse, o.mTwoColorDiffuse, PropSyncTwoColor(o))
    SYNC_PROP_MODIFY_ALT(two_color_interp, o.mTwoColorInterp, PropSyncTwoColor(o))
    SYNC_PROP_MODIFY_ALT(two_color_mask, o.mTwoColorMask, PropSyncTwoColor(o))
    SYNC_PROP_MODIFY_ALT(color1_palette, o.mColor1Palette, gOutfitConfigOwner->Recompose())
    SYNC_PROP_MODIFY_ALT(color1_option, o.mColor1Option, gOutfitConfigOwner->Recompose())
    SYNC_PROP_MODIFY_ALT(color2_palette, o.mColor2Palette, gOutfitConfigOwner->Recompose())
    SYNC_PROP_MODIFY_ALT(color2_option, o.mColor2Option, gOutfitConfigOwner->Recompose())
    SYNC_PROP_MODIFY_ALT(textures, o.mTextures, gOutfitConfigOwner->Recompose())
    SYNC_PROP(two_color, o.mTwoColor)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(OutfitConfig::MeshAO::Seam)
    SYNC_PROP(index, o.mIndex)
    SYNC_PROP(coeff, o.mCoeff)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(OutfitConfig::MeshAO)
    SYNC_PROP(meshname, o.mMeshName)
    SYNC_PROP(coeffs, o.mCoeffs)
    SYNC_PROP(seams, o.mSeams)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(OutfitConfig::Overlay)
    SYNC_PROP(category, o.mCategory)
    SYNC_PROP(texture, o.mTexture)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(OutfitConfig)
    gOutfitConfigOwner = this;
    SYNC_PROP_MODIFY_ALT(primary_color, mColors[0], Recompose())
    SYNC_PROP_MODIFY_ALT(secondary_color, mColors[1], Recompose())
    SYNC_PROP_MODIFY_ALT(tertiary_color, mColors[2], Recompose())
    SYNC_PROP(mats, mMats)
    SYNC_PROP(meshao, mMeshAO)
    SYNC_PROP(compute_ao, mComputeAO)
    SYNC_PROP(patches, mPatches)
    SYNC_PROP(perma_project, mPermaProject)
    SYNC_PROP(piercings, mPiercings)
    SYNC_PROP(overlays, mOverlays)
    SYNC_PROP(tex_blender, mTexBlender)
    SYNC_PROP(wrinkle_blender, mWrinkleBlender)
    SYNC_PROP(band_logo, mBandLogo)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS