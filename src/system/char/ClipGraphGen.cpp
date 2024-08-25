#include "char/ClipGraphGen.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

ClipGraphGenerator::ClipGraphGenerator() : unk1c(0), mDmap(0), mClipA(0), mClipB(0) {

}

ClipGraphGenerator::~ClipGraphGenerator(){}

ClipDistMap* ClipGraphGenerator::GeneratePair(CharClip* c1, CharClip* c2, ClipDistMap::Node* n1, ClipDistMap::Node* n2){
    c1->mTransitions.RemoveNodes(c2);
    bool b2 = true;
    unk1c = c1->mTypeDef;
    bool b1 = true;
    if(unk1c){
        if(c2->Type() == c1->Type()) b1 = false;
    }
    if(!b1 && ((c1->mPlayFlags & 0xF0) != 0x10)) b2 = false;
    if(b2) return 0;
    else {
        DataArray* transarr = unk1c->FindArray("on_transition", false);
        if(!transarr) return 0;
        else {
            static DataNode& a_clip = DataVariable("a_clip");
            static DataNode& b_clip = DataVariable("b_clip");
            mDmap = 0;
            a_clip = DataNode(c1);
            b_clip = DataNode(c2);
            mClipA = c1;
            mClipB = c2;
            transarr->ExecuteScript(1, this, 0, 1);
            ClipDistMap* dmap = mDmap;
            mDmap = 0;
            if(dmap) dmap->SetNodes(n1, n2);
            return dmap;
        }
    }
}

BEGIN_HANDLERS(ClipGraphGenerator)
    HANDLE(generate_transitions, OnGenerateTransitions)
    HANDLE_CHECK(0xC0)
END_HANDLERS

DataNode ClipGraphGenerator::OnGenerateTransitions(DataArray* da){
    MILO_ASSERT(!mDmap, 0xC6);
    MILO_ASSERT(mClipA, 199);
    MILO_ASSERT(mClipB, 200);
    float max_error = 1e+30f;
    da->FindData("max_error", max_error, false);
    float beat_align = 0;
    da->FindData("beat_align", beat_align, false);
    float blend_width = 1.0f;
    da->FindData("blend_width", blend_width, false);
    float max_facing = 0;
    da->FindData("max_facing", max_facing, false);
    float max_dist = 0;
    da->FindData("max_dist", max_dist, false);
    float end_dist = 0;
    da->FindData("end_dist", end_dist, false);
    DataArray* restrictArr = da->FindArray("restrict", false);

    int bflag = mClipB->mPlayFlags >> 12 & 15;
    int aflag = mClipA->mPlayFlags >> 12 & 15;
    if(bflag < aflag) aflag = bflag;
    if(beat_align < (float)aflag) beat_align = aflag;

    DataArray* boneweightarr = unk1c->FindArray("transition_bone_weights", false);
    mDmap = new ClipDistMap(mClipA, mClipB, beat_align, blend_width, 3, boneweightarr);
    mDmap->FindDists(max_facing * DEG2RAD, restrictArr);
    mDmap->FindNodes(max_error, max_dist, end_dist);
    return DataNode(0);
}