#include "bandobj/OutfitConfig.h"
#include "rndobj/Cam.h"
#include "utl/Symbols.h"

INIT_REVS(OutfitConfig);

RndMat* OutfitConfig::sMat;
RndCam* OutfitConfig::sCam;
BandCharDesc* OutfitConfig::sBandCharDesc;
OutfitConfig* gOutfitConfigOwner;

OutfitConfig::MatSwap::MatSwap(Hmx::Object* o) : mMat(o, 0), mResourceMat(o, 0), mTwoColorDiffuse(o, 0), mTwoColorInterp(o, 0), mTwoColorMask(o, 0), mColor1Palette(o, 0),
    mColor1Option(0), mColor2Palette(o, 0), mColor2Option(0), mTextures(o), mTwoColor(0) {

}

void OutfitConfig::MatSwap::SyncTwoColor(){
    mTwoColor = mTwoColorDiffuse || mTwoColorInterp || mTwoColorMask;
}

bool OutfitConfig::MatSwap::MatchesPatchCategory(int i, ObjVector<BandPatchMesh>& vec){
    if(!mMat) return false;
    else if(i == -1) return true;
    else {
        for(ObjVector<BandPatchMesh>::iterator it = vec.begin(); it != vec.end(); ++it){
            if(i & (*it).mCategory){
                for(ObjVector<BandPatchMesh::MeshPair>::iterator mp = (*it).mMeshes.begin(); mp != (*it).mMeshes.end(); ++mp){
                    MILO_ASSERT(mp->mesh, 0x6B);
                    if(mp->mesh->mMat == mMat) return true;
                }
            }
        }
        return false;
    }
}

void OutfitConfig::MatSwap::SwapResource(){
    if(mResourceMat){
        static Symbol mn("Mesh");
        std::vector<ObjRef*> refs;
        {
            MemDoTempAllocations m(true, false);
            refs = mResourceMat->Refs();
        }
        for(std::vector<ObjRef*>::reverse_iterator rit = refs.rbegin(); rit != refs.rend(); ++rit){
            ObjRef* cur = *rit;
            bool replace = false;
            if(cur->RefOwner()){
                if(cur->RefOwner()->ClassName() == mn) replace = true;
            }
            if(replace) cur->Replace(mResourceMat, mMat);
        }
    }
}

void OutfitConfig::MatSwap::UnSwapResource(){
    if(mResourceMat && mMat){
        static Symbol mn("Mesh");
        std::vector<ObjRef*> refs;
        {
            MemDoTempAllocations m(true, false);
            refs = mMat->Refs();
        }
        for(std::vector<ObjRef*>::reverse_iterator rit = refs.rbegin(); rit != refs.rend(); ++rit){
            ObjRef* cur = *rit;
            bool replace = false;
            if(cur->RefOwner()){
                if(cur->RefOwner()->ClassName() == mn) replace = true;
            }
            if(replace) cur->Replace(mMat, mResourceMat);
        }
    }
}

OutfitConfig::Piercing::Piercing(Hmx::Object* o) : mPiercing(o, 0), mReskin(0), mPieces(o) {

}

RndMesh* OutfitConfig::Piercing::GetHeadMesh(){
    return mPiercing.Owner()->Dir()->Find<RndMesh>("head.mesh", false);
}

OutfitConfig::Overlay::Overlay(Hmx::Object* o) : mCategory(0), mTexture(o, 0) {

}

void OutfitConfig::Init(){
    Register();
    sMat = Hmx::Object::New<RndMat>();
    sCam = Hmx::Object::New<RndCam>();
    sBandCharDesc = Hmx::Object::New<BandCharDesc>();
}

void OutfitConfig::Terminate(){
    RELEASE(sMat);
    RELEASE(sCam);
    RELEASE(sBandCharDesc);
}

OutfitConfig::OutfitConfig() : mMats(this), unk38(0), unk3c(0), mComputeAO(1), mPatches(this), mPermaProject(0), mPiercings(this),
    mTexBlender(this, 0), mWrinkleBlender(this, 0), mOverlays(this), mBandLogo(this, 0) {
    for(int i = 0; i < 3; i++) mColors[i] = i;
}

void OutfitConfig::SetColors(const int* cols){
    bool recomp = false;
    for(int i = 0; i < 3; i++){
        if(cols[i] != -1 && mColors[i] != cols[i]){
            mColors[i] = cols[i];
            recomp = true;
        }
    }
    if(recomp) Recompose();
}

void OutfitConfig::Recompose(){ unk38 = -1; }

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