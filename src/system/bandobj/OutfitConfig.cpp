#include "bandobj/OutfitConfig.h"
#include "math/Rand.h"
#include "rndobj/Cam.h"
#include "rndobj/Dir.h"
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

void OutfitConfig::RecomposePatches(int flag){
    for(int i = 0; i < mPatches.size(); i++){
        if(flag & mPatches[i].mCategory){
            unk38 |= flag;
        }
    }
}

void OutfitConfig::SetSkinTextures(ObjectDir* dir1, ObjectDir* dir2, BandCharDesc* desc){
    static const char* skinMats[] = { "torso_naked.mat", "torso", "legs_skin.mat", "legs", "feet_skin.mat", "legs", "feet_socks_skin.mat", "legs", "head_naked.mat", "head" };
    OutfitConfig* cfg = dir2->Find<OutfitConfig>("skin.cfg", false);
    Symbol gender = desc->mGender;
    for(int i = 0; i < 5; i++){
        const char* curtexname = skinMats[i * 2];
        RndMat* curmat = dir1->Find<RndMat>(skinMats[i * 2], false);
        if(curmat){
            RndTex* curtex = dir1->Find<RndTex>(MakeString("%s_%s_diff.tex", gender, curtexname), false);
            if(curtex){
                if(!cfg) curmat->SetDiffuseTex(curtex);
                else {
                    // switch(i){
                    //     case 0:
                    //     case 1:
                    //         break;
                    //     case 4:
                    //         break;
                    //     default: break;
                    // }
                    if(i < 2 || i == 4){
                        int idx = 2;
                        if(i != 4) idx = i;
                        MatSwap& curswap = cfg->mMats[idx];
                        curswap.mTwoColorDiffuse = curtex;
                        RndTex* interptex = dir1->Find<RndTex>(MakeString("%s_%s_interp_gw.tex", gender, curtexname), false);
                        if(interptex) curswap.mTwoColorInterp = interptex;
                    }
                    RndTex* difftex = dir2->Find<RndTex>(MakeString("%s_skin_diffuse_output.tex", curtexname), false);
                    if(difftex) curmat->SetDiffuseTex(difftex);
                }
            }
        }
        else MILO_WARN("%s could not find %s", PathName(dir1), skinMats[i * 2]);
    }
    if(cfg){
        RndMesh* torsomesh = dir1->Find<RndMesh>(MakeString("%s_tattoo_torso.mesh", gender), false);
        if(torsomesh) torsomesh->SetMat(dir1->Find<RndMat>("torso_naked.mat", false));
        RndMesh* legsmesh = dir1->Find<RndMesh>(MakeString("%s_tattoo_legs.mesh", gender), false);
        if(legsmesh) legsmesh->SetMat(dir1->Find<RndMat>("legs_skin.mat", false));
        RndMesh* headmesh = dir1->Find<RndMesh>(MakeString("%s_tattoo_head.mesh", gender), false);
        if(headmesh) headmesh->SetMat(dir1->Find<RndMat>("head_naked.mat", false));
    }
}

BinStream& operator>>(BinStream& bs, OutfitConfig::MatSwap& swap){
    bs >> swap.mMat;
    bs >> swap.mResourceMat;
    if(OutfitConfig::gRev < 5){
        bool b; bs >> b;
    }
    else {
        bs >> swap.mTwoColorDiffuse;
        bs >> swap.mTwoColorInterp;
    }
    bs >> swap.mTwoColorMask;
    if(OutfitConfig::gRev > 4){
        bs >> swap.mColor1Palette;
        bs >> swap.mColor1Option;
        bs >> swap.mColor2Palette;
        bs >> swap.mColor2Option;
        bs >> swap.mTextures;
    }
    swap.SyncTwoColor();
    return bs;
}

BinStream& operator>>(BinStream& bs, OutfitConfig::Piercing::Piece& piece){
    if(OutfitConfig::gRev > 0xF) bs >> piece.mVert;
    else {
        piece.mVert = -1;
        int i, j;
        bs >> i; bs >> j;
    }
    if(OutfitConfig::gRev < 0xF){ bool b; bs >> b; }
    if(OutfitConfig::gRev < 0xE){
        Transform tf;
        bs >> tf;
        std::vector<unsigned short> vec;
        bs >> vec;
    }
    else bs >> piece.mAttachment;
    bs >> piece.unk14;
    if(OutfitConfig::gRev < 0x1A && !piece.mAttachment){
        piece.mVert = -1;
        piece.unk14.clear();
    }
    return bs;
}

BinStream& operator>>(BinStream& bs, OutfitConfig::Piercing& piercing){
    bs >> piercing.mPiercing;
    if(OutfitConfig::gRev < 0xD){

    // ObjPtr<RndTransformable, ObjectDir> mPiercing; // 0x0
    //     Transform unkc; // 0xc
    //     bool mReskin; // 0x3c
    //     ObjVector<Piece> mPieces; // 0x40

    }
    else {
        bs >> piercing.unkc;
        if(OutfitConfig::gRev < 0xE){ bool b; bs >> b; }
        if(OutfitConfig::gRev == 0x10){ bool b; bs >> b; }
        bs >> piercing.mPieces;
        if(OutfitConfig::gRev > 0x1A) bs >> piercing.mReskin;
    }
    return bs;
}

BinStream& operator>>(BinStream& bs, OutfitConfig::Overlay& o){
    bs >> o.mCategory;
    bs >> o.mTexture;
    return bs;
}

BinStream& operator>>(BinStream& bs, OutfitConfig::MeshAO::Seam& seam){
    bs >> seam.mIndex;
    bs >> seam.mCoeff;
    return bs;
}

BinStream& operator>>(BinStream& bs, OutfitConfig::MeshAO& ao){
    bs >> ao.mMeshName;
    if(
        OutfitConfig::gRev == 9 || OutfitConfig::gRev == 10 || OutfitConfig::gRev == 11 || OutfitConfig::gRev == 12 || OutfitConfig::gRev == 13 ||
        OutfitConfig::gRev == 14 || OutfitConfig::gRev == 15 || OutfitConfig::gRev == 16 || OutfitConfig::gRev == 17 || OutfitConfig::gRev == 18 ||
        OutfitConfig::gRev == 19 || OutfitConfig::gRev == 20 || OutfitConfig::gRev == 21 || OutfitConfig::gRev == 22
    ){
        CSHA1::Digest d;
        bs >> d;
    }
    bs >> ao.mCoeffs;
    bs >> ao.mSeams;
    if(OutfitConfig::gRev > 0x18) bs >> ao.unkc;
    return bs;
}

SAVE_OBJ(OutfitConfig, 0x5C7)

BinStream& operator>>(BinStream& bs, OldMatOption& o){
    bs >> o.mMat;
    bs >> o.mPrimaryPalette;
    if(OutfitConfig::gRev != 0) bs >> o.mSecondaryPalette;
    bs >> o.mTexs;
    return bs;
}

BinStream& operator>>(BinStream& bs, OldColorOption& o){
    bs >> o.mColorIndex;
    bs >> o.mMatOptions;
    return bs;
}

#pragma push
#pragma dont_inline on
BEGIN_LOADS(OutfitConfig)
    LOAD_REVS(bs)
    ASSERT_REVS(0x1B, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if(gRev > 4){
        bs >> mColors[0];
        bs >> mColors[1];
        if(gRev > 10) bs >> mColors[2];
    }
    if(gRev > 3) bs >> mMats;
    if(gRev < 5){
        ObjVector<OldColorOption> colors(this);
        bs >> colors;
        for(int i = 0; i < colors.size(); i++){
            OldColorOption& curColor = colors[i];
            mColors[i] = curColor.mColorIndex;
            for(ObjList<OldMatOption>::iterator it = curColor.mMatOptions.begin(); it != curColor.mMatOptions.end(); ++it){
                int m;
                for(m = 0; m < mMats.size(); m++){
                    if(mMats[m].mMat == it->mMat) break;
                    if(mMats[m].mResourceMat == it->mMat) break;
                }
                if(m == mMats.size()){
                    mMats.push_back();
                    mMats.back().mResourceMat = it->mMat;
                    mMats.back().mMat = it->mMat;
                }
                MatSwap& curSwap = mMats[m];
                if(it->mTexs.size() != 0){
                    curSwap.mTextures = it->mTexs;
                    curSwap.mColor1Option = i;
                }
                if(it->mPrimaryPalette){
                    curSwap.mColor1Palette = it->mPrimaryPalette;
                    curSwap.mColor1Option = i;
                }
                if(it->mSecondaryPalette){
                    curSwap.mColor2Palette = it->mSecondaryPalette;
                    curSwap.mColor2Option = i;
                }
            }
        }
        if(gRev != 0){
            if(gRev < 2){
                ObjVector<ObjPtr<RndDir, ObjectDir> > dirs(this);
                bs >> dirs;
            }
            else if(gRev < 1){
                ObjVector<ObjPtr<RndDir, ObjectDir> > dirs(this);
                bs >> dirs;
            }
        }
    }
    if(gRev > 6) bs >> mMeshAO;
    if(gRev > 7) bs >> mComputeAO;
    if(gRev > 9) bs >> mPatches;
    if(gRev > 0xB) bs >> mPiercings;
    if(gRev > 0x12) bs >> mTexBlender;
    if(gRev > 0x13) bs >> mOverlays;
    if(gRev > 0x14) bs >> mBandLogo;
    if(gRev > 0x15) bs >> mDigest;
    if(gRev > 0x17) bs >> mWrinkleBlender;
END_LOADS

BEGIN_COPYS(OutfitConfig)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(OutfitConfig)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mColors[0])
        COPY_MEMBER(mColors[1])
        COPY_MEMBER(mColors[2])
        COPY_MEMBER(mMats)
        COPY_MEMBER(mMeshAO)
        COPY_MEMBER(mPiercings)
        COPY_MEMBER(mOverlays)
        COPY_MEMBER(mComputeAO)
        COPY_MEMBER(mTexBlender)
        COPY_MEMBER(mWrinkleBlender)
        COPY_MEMBER(mBandLogo)
        Recompose();
    END_COPYING_MEMBERS
END_COPYS
#pragma pop

void OutfitConfig::PreSave(BinStream& bs){
    for(ObjVector<MatSwap>::iterator it = mMats.begin(); it != mMats.end(); ++it){
        it->UnSwapResource();
    }
    Recompose();
}

void OutfitConfig::PostSave(BinStream&){}
void OutfitConfig::UpdatePreClearState(){
    TheRnd->PreClearDrawAddOrRemove(this, true, false);
}

BandCharDesc* OutfitConfig::FindBandCharDesc(){
    if(Dir()){
        static Symbol sBandCharName("BandCharacter");
        if(Dir()->ClassName() == sBandCharName){
            
        }
    }
    const char* str = strstr(Dir()->GetPathName(), "female");
    sBandCharDesc->SetGender(str ? "female" : "male");
    return sBandCharDesc;
}

void OutfitConfig::Randomize(){
    for(int i = 0; i < 3; i++){
        int num = NumIndices(i);
        if(num != 0) mColors[i] = RandomInt(0, num);
    }
    Recompose();
}

void OutfitConfig::CompressTextures(){
    if(unk3c != 2) unk3c = 1;
}

void OutfitConfig::ApplyAO(SyncMeshCB* mesh){
    for(int i = 0; i < mMeshAO.size(); i++){
        mMeshAO[i].Apply(this, mesh);
    }
    for(int i = 0; i < mPiercings.size(); i++){
        mPiercings[i].Deform(mesh);
    }
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