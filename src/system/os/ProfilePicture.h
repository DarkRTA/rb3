#ifndef OS_PROFILEPICTURE_H
#define OS_PROFILEPICTURE_H
#include "obj/Object.h"
#include "os/OnlineID.h"
#include "obj/Msg.h"

class RndTex; // forward dec

enum State {
    kIdle,
    kFetchingUserData,
    kFetchingUserPicture,
    kComplete
};

class ProfilePicture {
public:
    ProfilePicture(int, Hmx::Object*);
    ~ProfilePicture();

    void FetchUserData();
    bool ReceiveUserData();
    void FetchUserPicture();
    bool ReceiveUserPicture();

    void Update();
    void Poll();
    void Succeed();

    State mState;
    OnlineID mUserID;
    RndTex* mUserPicture;
    int mPadNum;
    Hmx::Object* mCallback;
};

BEGIN_MESSAGE(ProfilePictureFetchedMsg, profile_picture_fetched_msg, int);
    // MESSAGE_ARRAY_CTOR(ProfilePictureFetchedMsg)
END_MESSAGE;

inline ProfilePictureFetchedMsg::ProfilePictureFetchedMsg(int i) :
    Message(Type(), DataNode(i)) {}

#endif
