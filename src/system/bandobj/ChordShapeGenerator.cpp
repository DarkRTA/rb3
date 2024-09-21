#include "bandobj/ChordShapeGenerator.h"
#include "beatmatch/RGUtl.h"
#include "utl/Symbols.h"

INIT_REVS(ChordShapeGenerator);

ChordShapeGenerator::ChordShapeGenerator() : mFingerSrcMesh(this, 0), mChordSrcMesh(this, 0), mBaseXSection(this, 0), mContourXSection(this, 0), mBaseHeight(this, 0),
    mNumSlots(6), mString0(this, 0), mString1(this, 0), mString2(this, 0), mString3(this, 0), mString4(this, 0), mString5(this, 0), unkc4(0), unkc8(-1.0f), unkcc(1.0f), unkd0(0.2f) {
    mFretHeights.resize(6);
    for(int i = 0; i < 7; i++) mFretHeights[i] = 1.0f;
    mGradeDistances.resize(6);
    for(int i = 0; i < 6; i++) mGradeDistances[i] = 0.33f;
    mStringFrets.resize(6);
    for(int i = 0; i < 6; i++) mStringFrets[i] = -1;
    unk64.resize(6);
    for(int i = 0; i < 6; i++) unk64[i] = 1;
}

BEGIN_COPYS(ChordShapeGenerator)
    CREATE_COPY(ChordShapeGenerator)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mChordSrcMesh)
        COPY_MEMBER(mFingerSrcMesh)
        COPY_MEMBER(mBaseXSection)
        COPY_MEMBER(mContourXSection)
        COPY_MEMBER(mBaseHeight)
        COPY_MEMBER(mNumSlots)
        COPY_MEMBER(mString0)
        COPY_MEMBER(mString1)
        COPY_MEMBER(mString2)
        COPY_MEMBER(mString3)
        COPY_MEMBER(mString4)
        COPY_MEMBER(mString5)
        COPY_MEMBER(mFretHeights)
        COPY_MEMBER(mGradeDistances)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(ChordShapeGenerator, 0x43)

#define kMaxFretHeights 6

BEGIN_LOADS(ChordShapeGenerator)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    bs >> mChordSrcMesh;
    if(gRev != 0) bs >> mFingerSrcMesh;
    bs >> mBaseXSection;
    bs >> mContourXSection;
    bs >> mBaseHeight;
    bs >> mNumSlots;
    bs >> mStringFrets;
    bs >> mString0;
    bs >> mString1;
    bs >> mString2;
    bs >> mString3;
    bs >> mString4;
    bs >> mString5;
    bs >> mFretHeights;
    bs >> mGradeDistances;
    MILO_ASSERT(mFretHeights.size() <= (kMaxFretHeights + 1), 0x70);
    MILO_ASSERT(mGradeDistances.size() <= kMaxFretHeights, 0x71);
    while(mFretHeights.size() < 7){
        mFretHeights.push_back(mFretHeights.back());
    }
    while(mGradeDistances.size() < 6) mGradeDistances.push_back(0);
END_LOADS

RndMesh* NewCopyMesh(const RndMesh* mesh){
    RndMesh* ret = Hmx::Object::New<RndMesh>();
    ret->Copy(mesh, Hmx::Object::kCopyDeep);
    return ret;
}

const Transform& ChordShapeGenerator::SlotXfm(int idx) const {
    switch(idx){
        case 0: return mString0->WorldXfm();
        case 1: return mString1->WorldXfm();
        case 2: return mString2->WorldXfm();
        case 3: return mString3->WorldXfm();
        case 4: return mString4->WorldXfm();
        case 5: return mString5->WorldXfm();
        default:
            MILO_WARN("string index %d out of range", idx);
            static Transform t;
            return t;
    }
}

bool ChordShapeGenerator::CheckParams() const {
    bool missing = false;
    if(!mChordSrcMesh){
        MILO_WARN("%s is missing", "source chord mesh");
        missing = true;
    }
    if(!mFingerSrcMesh){
        MILO_WARN("%s is missing", "source finger mesh");
        missing = true;
    }
    if(!mBaseXSection){
        MILO_WARN("%s is missing", "base cross section transform");
        missing = true;
    }
    if(!mContourXSection){
        MILO_WARN("%s is missing", "contour cross section transform");
        missing = true;
    }
    if(!mBaseHeight){
        MILO_WARN("%s is missing", "base height transform");
        missing = true;
    }
    if(!mString0){
        MILO_WARN("%s is missing", "smasher 0");
        missing = true;
    }
    if(!mString1){
        MILO_WARN("%s is missing", "smasher 1");
        missing = true;
    }
    if(!mString2){
        MILO_WARN("%s is missing", "smasher 2");
        missing = true;
    }
    if(!mString3){
        MILO_WARN("%s is missing", "smasher 3");
        missing = true;
    }
    if(!mString4){
        MILO_WARN("%s is missing", "smasher 4");
        missing = true;
    }
    if(!mString5){
        MILO_WARN("%s is missing", "smasher 5");
        missing = true;
    }
    return missing;
}

int shapesGenerated;
int cycles;

void ChordShapeGenerator::DumpChordGenData(){
    if(shapesGenerated > 0){
        MILO_LOG("Chord Shape Generator: built %d shapes in %.2f mS\n", shapesGenerated, Timer::CyclesToMs(cycles)); // probably the wrong timer func
    }
    shapesGenerated = 0;
    cycles = 0;
}

RndMesh* ChordShapeGenerator::BuildChordMesh(unsigned int ui, int i){
    RGUnpackChordShapeID(ui, mStringFrets, &unk64);
    shapesGenerated++;
    BuildChordMesh();
}

RndMesh* ChordShapeGenerator::MakeInvertedMesh(const RndMesh* mesh){
    RndMesh* ret = NewCopyMesh(mesh);
    for(int i = 0; i < (int)ret->Verts().size(); i++){
        RndMesh::Vert& curvert = ret->Verts()[i];
        curvert.pos.x = -curvert.pos.x;
        curvert.norm.x = -curvert.norm.x;
    }
    for(int i = 0; i < ret->Faces().size(); i++){
        RndMesh::Face& curface = ret->Faces()[i];
        int temp = curface.idx1;
        curface.idx1 = curface.idx2;
        curface.idx2 = temp;
    }
    if(TheLoadMgr.EditMode()){
        ret->Sync(0x3F);
        ret->SetMutable(0);
    }
    return ret;
}

int vertIt; // this type might be wrong

#pragma push
#pragma dont_inline on
void ChordShapeGenerator::BuildContourCap(RndMesh* mesh, std::map<unsigned short, unsigned short>& connectingVerts, int iii,
    const Transform& tf1, const Transform& tf2, Symbol sym, Hmx::Color32 col1, Hmx::Color32 col2){
    MILO_ASSERT(connectingVerts.size(), 0x24B);
    RndMesh::VertVector& verts = unkc4->Verts();
    std::map<unsigned short, unsigned short> map150;
    for(int i = 0; i < verts.size(); i++){
        RndMesh::Vert& curvert = verts[i];
        if(curvert.pos.x > unkc8 + 0.1f && curvert.pos.x < unkcc - 0.1f){
            map150[i] = vertIt++;
        }
    }
    bool isright = sym == right;
    RndMesh::VertVector& meshverts = mesh->Verts();
    if(vertIt > meshverts.size()){
        unsigned int newsize = meshverts.size() * 2;
        MILO_LOG("RG: too few verts for chord shape - increasing to %d", newsize);
        meshverts.resize(newsize, true);
    }
    Transform tfd8;
    Transform tf108;
    Transform tf138;
    InterpolateXfm(tf1, tf2, 0.33f, tfd8);
    InterpolateXfm(tf1, tf2, 0.67f, tf108);
    InterpolateXfm(tf1, tf2, 0.50f, tf138);
    tf138.v = tfd8.v;
    tf138.v += tf108.v;
    tf138.v /= 2.0f;
    float f6 = (unkc8 * 2.0f + unkcc) / 3.0f;
    float f7 = (unkcc * 2.0f + unkc8) / 3.0f;
    float f22 = (tf2.v.x - tf1.v.x) / (unkcc - unkc8);
    float f23 = -f22;
    float var29 = (unkc8 + unkcc) / 2.0f;
    float var28 = mFretHeights[iii];
    std::map<unsigned short, unsigned short>::iterator it = map150.begin();
    std::map<unsigned short, unsigned short>::iterator itEnd = map150.end();
    for(; it != itEnd; ++it){
        RndMesh::Vert& curvert = meshverts[it->first];
        curvert = verts[it->first];
        if(isright){
            if(curvert.pos.x < f6){
                TransformVert(curvert, unkc8, f23, var28, tf2, Hmx::Color32(col2));
            }
            else if(curvert.pos.x < f7){
                TransformVert(curvert, var29, f23, var28, tf138, Hmx::Color32(col2));
            }
            else {
                TransformVert(curvert, unkcc, f23, var28, tf1, Hmx::Color32(col2));
            }
        }
        else {
            if(curvert.pos.x < f6){
                TransformVert(curvert, unkc8, f22, var28, tf1, Hmx::Color32(col1));
            }
            else if(curvert.pos.x < f7){
                TransformVert(curvert, var29, f22, var28, tf138, Hmx::Color32(col1));
            }
            else {
                TransformVert(curvert, unkcc, f22, var28, tf2, Hmx::Color32(col1));
            }
        }
    }
    std::map<unsigned short, unsigned short> map168;
    AddVertProfile(mesh, tf2, var29, isright ? sec2 : sec1, map168, Hmx::Color32(isright ? col2 : col1));
    map150.insert(map168.begin(), map168.end());
    map150.insert(map168.begin(), map168.end()); // fix
    std::vector<RndMesh::Face>& faces = unkc4->Faces();
    std::vector<RndMesh::Face>& meshfaces = mesh->Faces();
    for(int i = 0; i < faces.size(); i++){
        // idek
    }
    connectingVerts.swap(map168);
}
#pragma pop

DataNode ChordShapeGenerator::OnGenerate(const DataArray* da){
    RndMesh* mesh = BuildChordMesh();
    NameMesh(mesh, false);
    return DataNode(mesh);
}

DataNode ChordShapeGenerator::OnInvert(const DataArray* da){
    RndMesh* mesh = da->Obj<RndMesh>(2);
    if(mesh){
        mesh = MakeInvertedMesh(mesh);
        NameMesh(mesh, true);
        return DataNode(mesh);
    }
    else return DataNode(0);
}

DataNode ChordShapeGenerator::OnSetStringFret(const DataArray* da){
    int fret = da->Int(3);
    mStringFrets[da->Int(2)] = fret;
    return DataNode(fret);
}

DataNode ChordShapeGenerator::OnGetStringTrans(const DataArray* da){
    int idx = da->Int(2);
    switch(idx){
        case 0: return DataNode(mString0);
        case 1: return DataNode(mString1);
        case 2: return DataNode(mString2);
        case 3: return DataNode(mString3);
        case 4: return DataNode(mString4);
        case 5: return DataNode(mString5);
        default: return DataNode(0);
    }
}

BEGIN_HANDLERS(ChordShapeGenerator)
    HANDLE(generate_chord_shape, OnGenerate)
    HANDLE(invert_chord_shape, OnInvert)
    HANDLE(set_string_fret, OnSetStringFret)
    HANDLE(get_string_trans, OnGetStringTrans)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x40A)
END_HANDLERS

BEGIN_PROPSYNCS(ChordShapeGenerator)
    SYNC_PROP(chord_source_mesh, mChordSrcMesh)
    SYNC_PROP(finger_source_mesh, mFingerSrcMesh)
    SYNC_PROP(base_cross_section, mBaseXSection)
    SYNC_PROP(contour_cross_section, mContourXSection)
    SYNC_PROP(base_height, mBaseHeight)
    SYNC_PROP(num_slots, mNumSlots)
    SYNC_PROP(string_0_fret, mStringFrets[0])
    SYNC_PROP(string_1_fret, mStringFrets[1])
    SYNC_PROP(string_2_fret, mStringFrets[2])
    SYNC_PROP(string_3_fret, mStringFrets[3])
    SYNC_PROP(string_4_fret, mStringFrets[4])
    SYNC_PROP(string_5_fret, mStringFrets[5])
    SYNC_PROP(string_0, mString0)
    SYNC_PROP(string_1, mString1)
    SYNC_PROP(string_2, mString2)
    SYNC_PROP(string_3, mString3)
    SYNC_PROP(string_4, mString4)
    SYNC_PROP(string_5, mString5)
    SYNC_PROP(fret_height_1, mFretHeights[1])
    SYNC_PROP(fret_height_2, mFretHeights[2])
    SYNC_PROP(fret_height_3, mFretHeights[3])
    SYNC_PROP(fret_height_4, mFretHeights[4])
    SYNC_PROP(fret_height_5, mFretHeights[5])
    SYNC_PROP(fret_height_6, mFretHeights[6])
    SYNC_PROP(grade_distance_1, mGradeDistances[1])
    SYNC_PROP(grade_distance_2, mGradeDistances[2])
    SYNC_PROP(grade_distance_3, mGradeDistances[3])
    SYNC_PROP(grade_distance_4, mGradeDistances[4])
    SYNC_PROP(grade_distance_5, mGradeDistances[5])
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS