#include "char/ClipCollide.h"
#include "rndobj/Graph.h"
#include "char/Character.h"
#include "char/Waypoint.h"
#include "char/CharClip.h"
#include "char/CharDriver.h"
#include "utl/Symbols.h"

INIT_REVS(ClipCollide)

ClipCollide::ClipCollide() : mReports(), mGraph(0), mChar(this, 0), mCharPath(""), mWaypoint(this, 0), mPosition(Symbol("front")), mClip(this, 0), mWorldLines(0), mMoveCamera(1), mMode() {
    mGraph = RndGraph::Get(this);
}

ClipCollide::~ClipCollide(){
    RndGraph::Free(this, false);
}

void ClipCollide::SyncChar(){
    if(mChar){
        if(!mCharPath.empty()){
            FilePath fp(mCharPath.c_str());
            FilePath curproxy(mChar->ProxyFile());
            if(fp != curproxy){
                mChar->SetProxyFile(fp, false);
            }
        }
    }
    SyncWaypoint();
}

void ClipCollide::ClearReport(){
    mGraph->Reset();
    mReports.clear();
    mReportString = "";
    SyncMode();
}

void ClipCollide::Demonstrate(){
    bool b1 = false;
    if(mChar && mWaypoint && mClip) b1 = true;
    if(b1){
        SyncWaypoint();
        mChar->mDriver->Play(mClip, 2, -1.0f, 1e+30f, 0.0f);
    }
}

void ClipCollide::SetTypeDef(DataArray* da){
    if(mTypeDef != da){
        Hmx::Object::SetTypeDef(da);
        if(da){
            DataArray* modesArr = da->FindArray("modes", true);
            mMode = modesArr->Array(1)->Sym(0);
        }
    }
}

ObjectDir* ClipCollide::Clips(){
    if(mChar) return mChar->mDriver->ClipDir();
    else return 0;
}

bool ClipCollide::ValidWaypoint(Waypoint* w){
    static Message vw("valid_waypoint", DataNode(0));
    vw[0] = DataNode(w);
    DataNode handled = Handle(vw, true);
    if(handled.Type() == kDataUnhandled) return true;
    else return handled.Int();
}

bool ClipCollide::ValidClip(CharClip* clip){
    if(!mWaypoint) return true;
    else {
        static Message vw("valid_clip", DataNode(0), DataNode(0));
        vw[0] = DataNode(clip);
        vw[1] = DataNode(mWaypoint);
        DataNode handled = Handle(vw, true);
        if(handled.Type() == kDataUnhandled) return true;
        else return handled.Int();
    }
}

void ClipCollide::TestChars(){
    if(mChar){
        DataArray* td = mTypeDef;
        if(td){
            DataArray* charsArr = td->FindArray("chars", false);
            if(charsArr){
                DataArray* arr = charsArr->Array(1);
                for(int i = 0; i < arr->Size(); i++){
                    String str(arr->Str(i));
                    if(!str.empty()){
                        mCharPath = str;
                        SyncChar();
                        TestWaypoints();
                    }
                }
            }
        }
    }
}

void ClipCollide::TestWaypoints(){
    if(!mChar) return;
    for(ObjDirItr<Waypoint> it(Dir(), true); it != 0; ++it){
        if(ValidWaypoint(it)){
            mWaypoint = it;
            TestClips();
        }
    }
}

// std::vector<Report> mReports; // 0x1c
// RndGraph* mGraph; // 0x24
// ObjPtr<Character, ObjectDir> mChar; // 0x28
// String mCharPath; // 0x34
// ObjPtr<Waypoint, ObjectDir> mWaypoint; // 0x40
// Symbol mPosition; // 0x4c
// ObjPtr<CharClip, ObjectDir> mClip; // 0x50
// String mReportString; // 0x5c
// bool mWorldLines; // 0x68
// bool mMoveCamera; // 0x69
// Symbol mMode; // 0x6c

void ClipCollide::TestClips(){
    if(!mWaypoint || !mChar) return;
    for(ObjDirItr<CharClip> it(Clips(), true); it != 0; ++it){
        if(ValidClip(it)){
            const char* directions[4] = { "front", "back", "left", "right" };
            for(int i = 0; i < 4; i++){
                mPosition = directions[i];
                mClip = it;
                Collide();
            }
        }
    }
}

DataNode ClipCollide::OnVenueName(DataArray* da){
    String str;
    Hmx::Object* miloObj = ObjectDir::Main()->Find<Hmx::Object>("milo", true);
    if(miloObj){
        Message msg("current_file");
        DataNode handled = miloObj->Handle(msg, true);
        char buf[0x100];
        strcpy(buf, handled.Str());
        int len = strlen(buf);
        char* p = buf + len;
        if(buf <= p){
            for(; len != 0; len--, p--){
                if(*p == '\\' || *p == '/'){
                    *p = '\0';
                    break;
                }
            }
        }
        char* p1 = p + (1 - (int)buf);
        if(buf <= p){
            for(; p1 != 0; p1--, p--){
                if(*p == '\\' || *p == '/'){
                    str = buf;
                    break;
                }
            }
        }
    }
    return DataNode(str);
}

SAVE_OBJ(ClipCollide, 0x19D)

BEGIN_LOADS(ClipCollide)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    bs >> mChar;
    bs >> mCharPath;
    bs >> mWaypoint;
    bs >> mPosition;
    mClip = 0;
END_LOADS

BEGIN_COPYS(ClipCollide)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(ClipCollide)
END_COPYS

void ClipCollide::SyncMode(){
    if(!mMode.Null()){
        Message msg("set_mode", DataNode(mMode));
        Handle(msg, true);
    }
}

BEGIN_HANDLERS(ClipCollide)
    HANDLE(list_clips, OnListClips)
    HANDLE(list_waypoints, OnListWaypoints)
    HANDLE(list_report, OnListReport)
    HANDLE_ACTION(demonstrate, Demonstrate())
    HANDLE_ACTION(collide, Collide())
    HANDLE_ACTION(test_clips, TestClips())
    HANDLE_ACTION(test_waypoints, TestWaypoints())
    HANDLE_ACTION(test_chars, TestChars())
    HANDLE_ACTION(clear_report, ClearReport())
    HANDLE(venue_name, OnVenueName)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x1DC)
END_HANDLERS

DataNode ClipCollide::OnListClips(DataArray* da){
    std::list<CharClip*> cliplist;
    ObjectDir* clipDir = Clips();
    if(clipDir){
        for(ObjDirItr<CharClip> it(clipDir, true); it != 0; ++it){
            if(ValidClip(it)) cliplist.push_back(it);
        }
        // sort
    }
    int listsize = 0;
    for(std::list<CharClip*>::iterator it = cliplist.begin(); it != cliplist.end(); it++) listsize++;
    DataArray* arr = new DataArray(listsize);
    arr->Node(0) = DataNode((Hmx::Object*)0);
    int idx = 1;
    for(std::list<CharClip*>::iterator it = cliplist.begin(); it != cliplist.end(); it++){
        arr->Node(idx++) = DataNode(*it);
    }
    DataNode ret(arr, kDataArray);
    arr->Release();
    return ret;
}

DataNode ClipCollide::OnListWaypoints(DataArray* da){
    std::list<Waypoint*> waylist;
    for(ObjDirItr<Waypoint> it(Dir(), true); it != 0; ++it){
        if(ValidWaypoint(it)) waylist.push_back(it);
    }
    // sort
    int listsize = 0;
    for(std::list<Waypoint*>::iterator it = waylist.begin(); it != waylist.end(); it++) listsize++;
    DataArray* arr = new DataArray(listsize);
    arr->Node(0) = DataNode((Hmx::Object*)0);
    int idx = 1;
    for(std::list<Waypoint*>::iterator it = waylist.begin(); it != waylist.end(); it++){
        arr->Node(idx++) = DataNode(*it);
    }
    DataNode ret(arr, kDataArray);
    arr->Release();
    return ret;
}

DataNode ClipCollide::OnListReport(DataArray* da){
    DataArray* arr = new DataArray(mReports.size() + 1);
    arr->Node(0) = DataNode("");
    for(int i = 0; i < mReports.size(); i++){
        arr->Node(i + 1) = DataNode(MakeString("%d %s %s %s", i + 1, mReports[i].clip, mReports[i].waypoint->Name(), mReports[i].name));
    }
    DataNode ret(arr, kDataArray);
    arr->Release();
    return ret;
}

BEGIN_PROPSYNCS(ClipCollide)
    SYNC_PROP_MODIFY_ALT(character, mChar, SyncChar())
    SYNC_PROP_MODIFY_ALT(pick_character, mCharPath, SyncChar())
    SYNC_PROP_MODIFY_ALT(waypoint, mWaypoint, SyncWaypoint())
    SYNC_PROP_MODIFY(position, mPosition, SyncWaypoint())
    SYNC_PROP_MODIFY(mode, mMode, SyncMode())
    SYNC_PROP(clip, mClip)
    SYNC_PROP_SET(clips, Clips(), )
    SYNC_PROP_SET(pick_report, mReportString, PickReport(_val.Str()))
    SYNC_PROP(world_lines, mWorldLines)
    SYNC_PROP(move_camera, mMoveCamera)
END_PROPSYNCS
