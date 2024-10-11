#include "char/CharBoneDir.h"
#include "obj/DataFunc.h"
#include "char/CharUtl.h"
#include "obj/ObjVersion.h"
#include "utl/Symbols.h"

INIT_REVS(CharBoneDir)

ObjectDir* sResources;
DataArray* CharBoneDir::sCharClipTypes;

DataNode GetClipTypes(DataArray* da){ return CharBoneDir::GetClipTypes(); }

#pragma push
#pragma pool_data off
// fn_804A8BF0
void CharBoneDir::Init(){
    FilePathTracker tracker(FileRoot());
    sResources = ObjectDir::Main()->New<ObjectDir>("char_resources");
    DataArray* cfg = SystemConfig("objects", "CharBoneDir");
    const char* cc = "";
    cfg->FindData("resource_path", cc, false);
    sCharClipTypes = SystemConfig("objects", "CharClip", "types");
    if(sCharClipTypes && *cc != '\0'){
        for(int i = 1; i < sCharClipTypes->Size(); i++){
            DataArray* foundarr = sCharClipTypes->Array(i)->FindArray("resource", false);
            if(foundarr){
                Symbol foundsym = foundarr->Sym(1);
                ObjectDir* thedir = dynamic_cast<ObjectDir*>(sResources->FindObject(foundsym.Str(), false));
                if(!thedir){
                    const char* milostr = MakeString("%s/%s.milo", cc, foundsym);
                    static int _x = MemFindHeap("char");
                    MemPushHeap(_x);
                    ObjectDir* loaded = DirLoader::LoadObjects(FilePath(milostr), 0, 0);
                    if(loaded) loaded->SetName(foundsym.Str(), sResources);
                    MemPopHeap();
                }
            }
        }
    }
    // DataRegisterFunc("get_clip_types", GetClipTypes);
}
#pragma pop

void CharBoneDir::Terminate(){ delete sResources; }

CharBoneDir* CharBoneDir::FindResource(const char* cc){
    return sResources->Find<CharBoneDir>(cc, false);
}

CharBoneDir* CharBoneDir::FindResourceFromClipType(Symbol cliptype){
    DataArray* types = sCharClipTypes->FindArray(cliptype, false);
    if(!types){
        MILO_WARN("CharClip has no type %s", cliptype);
        return 0;
    }
    else {
        DataArray* resources = types->FindArray("resource", false);
        if(!resources){
            MILO_WARN("CharClip %s has no (resource ...) field", cliptype);
            return 0;
        }
        else {
            CharBoneDir* dir = FindResource(resources->Str(1));
            if(!dir) MILO_WARN("CharClip %s has no resource", cliptype);
            return dir;
        }
    }
}

CharBoneDir::CharBoneDir() : mRecenter(this), mMoveContext(0), mBakeOutFacing(1), mContextFlags(0), mFilterContext(0), mFilterBones(this, kObjListNoNull) {

}

CharBoneDir::~CharBoneDir(){

}

void CharBoneDir::StuffBones(CharBones& bones, int i){
    std::list<CharBones::Bone> blist;
    ListBones(blist, i, true);
    bones.AddBones(blist);
}

void CharBoneDir::StuffBones(CharBones& bones, Symbol sym){
    DataArray* found = sCharClipTypes->FindArray(sym, false);
    if(!found) MILO_WARN("CharClip has no type %s", sym);
    else {
        DataArray* resource = found->FindArray("resource", false);
        if(!resource) MILO_WARN("CharClip %s has no (resource ...) field", sym);
        else {
            CharBoneDir* dir = FindResource(resource->Str(1));
            if(!dir) MILO_WARN("CharClip %s has no resource", sym);
            else {
                dir->StuffBones(bones, DataGetMacro(resource->Str(2))->Int(0));
            }
        }
    }
}

DataNode CharBoneDir::GetClipTypes(){
    DataArray* arr = new DataArray(sCharClipTypes->Size());
    arr->Node(0) = DataNode(Symbol());
    for(int i = 1; i < sCharClipTypes->Size(); i++){
        DataArray* currArr = sCharClipTypes->Array(i);
        arr->Node(i) = DataNode(currArr->Sym(0));
    }
    arr->SortNodes();
    DataNode ret(arr, kDataArray);
    arr->Release();
    return ret;
}

void CharBoneDir::ListBones(std::list<CharBones::Bone>& bones, int mask, bool b){
    if(mMoveContext & mask){
        bones.push_back(CharBones::Bone("bone_facing.pos", 1.0f));
        bones.push_back(CharBones::Bone("bone_facing.rotz", 1.0f));
        if(b){
            bones.push_back(CharBones::Bone("bone_facing_delta.pos", 1.0f));
            bones.push_back(CharBones::Bone("bone_facing_delta.rotz", 1.0f));
        }
    }
    for(ObjDirItr<CharBone> it(this, true); it != 0; ++it){
        it->StuffBones(bones, mask);
    }
}

// fn_804A9A08
void CharBoneDir::MergeCharacter(const FilePath& fp){
    ObjectDir* dir = DirLoader::LoadObjects(FilePath(fp.c_str()), 0, 0);
    if(!dir) MILO_WARN("Could not load %s", fp);
    else {
        std::list<RndTransformable*> tlist;
        for(ObjDirItr<RndTransformable> it(dir, true); it != 0; ++it){
            if((Hmx::Object*)it != (Hmx::Object*)dir){
                if(CharUtlIsAnimatable(it)){
                    const char* name = it->Name();
                    if(strncmp("bone_", name, 5) == 0 || strncmp("exo_", name, 4) == 0){
                        tlist.push_back(it);
                    }
                }
            }
        }
        // ...
    }
}

// fn_804A9F54
DataNode CharBoneDir::GetContextFlags(){
    if(mContextFlags.Type() == kDataInt){
        DataArray* cfg = SystemConfig("objects", "CharClip", "types");
        DataArray* arr = new DataArray(cfg->Size() - 1);
        Symbol name(Name());
        int count = 0;
        for(int i = 1; i < arr->Size(); i++){
            DataArray* resourceArr = cfg->Array(i)->FindArray("resource", false);
            bool b = false;
            if(resourceArr && resourceArr->Sym(1) == name) b = true;
            if(b){
                const char* str = resourceArr->Str(2);
                int j;
                for(j = 0; j < count; j++){
                    bool strsmatch = strcmp(str, arr->Str(j)) == 0;
                    if(strsmatch) break;
                }
                if(j == count){
                    arr->Node(count++) = DataNode(resourceArr->Str(2));
                }
            }
        }
        arr->Resize(count);
        arr->SortNodes();
        mContextFlags = DataNode(arr, kDataArray);
        arr->Release();
    }
    return DataNode(mContextFlags);
}

void CharBoneDir::SyncFilter(){
    mFilterBones.clear();
    for(ObjDirItr<CharBone> it(this, true); it != 0; ++it){
        if(mFilterContext & it->PositionContext() ||
            mFilterContext & it->ScaleContext() ||
            (it->RotationType() != CharBones::TYPE_END &&
            mFilterContext & it->RotationContext())
        )
        mFilterBones.push_back(it);
    }
    // new objptrlist method called here - takes in a fn ptr too (gross)
}

BinStream& operator>>(BinStream& bs, CharBoneDir::Recenter& rc){
    bs >> rc.mTargets;
    bs >> rc.mAverage;
    bs >> rc.mSlide;
    return bs;
}

void CharBoneDir::Load(BinStream& bs){ ObjectDir::Load(bs); }
SAVE_OBJ(CharBoneDir, 0x18C)

void CharBoneDir::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    PushRev(packRevs(gAltRev, gRev), this);
    ObjectDir::PreLoad(bs);
}

void CharBoneDir::PostLoad(BinStream& bs){
    ObjectDir::PostLoad(bs);
    int revs = PopRev(this);
    gRev = getHmxRev(revs);
    gAltRev = getAltRev(revs);
    if(gRev < 2) bs.ReadBool();
    else bs >> mMoveContext;
    if(gRev < 3) bs.ReadBool();
    bs >> mRecenter;
    if(gRev > 3) bs >> mBakeOutFacing;
}

BEGIN_COPYS(CharBoneDir)
    COPY_SUPERCLASS(ObjectDir)
    CREATE_COPY(CharBoneDir)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mMoveContext)
        COPY_MEMBER(mRecenter)
        COPY_MEMBER(mBakeOutFacing)
    END_COPYING_MEMBERS
END_COPYS

BEGIN_HANDLERS(CharBoneDir)
    HANDLE_EXPR(get_context_flags, GetContextFlags())
    HANDLE_SUPERCLASS(ObjectDir)
    HANDLE_CHECK(0x1D1)
END_HANDLERS

BEGIN_CUSTOM_PROPSYNC(CharBoneDir::Recenter)
    SYNC_PROP(targets, o.mTargets)
    SYNC_PROP(average, o.mAverage)
    SYNC_PROP(slide, o.mSlide)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharBoneDir)
    SYNC_PROP(recenter, mRecenter)
    SYNC_PROP_SET(merge_character, "", MergeCharacter(FilePath(_val.Str())))
    SYNC_PROP(move_context, mMoveContext)
    SYNC_PROP(bake_out_facing, mBakeOutFacing)
    SYNC_PROP_MODIFY(filter_context, mFilterContext, SyncFilter())
    SYNC_PROP(filter_bones, mFilterBones)
    SYNC_PROP(filter_names, mFilterNames)
    SYNC_SUPERCLASS(ObjectDir)
END_PROPSYNCS
