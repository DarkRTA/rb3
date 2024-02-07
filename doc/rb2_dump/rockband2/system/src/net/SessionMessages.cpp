/*
    Compile unit: C:\rockband2\system\src\net\SessionMessages.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x805393D8 -> 0x8053AADC
*/
// Range: 0x805393D8 -> 0x805393EC
void SessionMsg::Dispatch() {
    // References
    // -> class Net TheNet;
}

// Range: 0x805393EC -> 0x80539474
int JoinRequestMsg::GetPlayerID(const class JoinRequestMsg * const this /* r30 */, int index /* r31 */) {
    // References
    // -> class Debug TheDebug;
    // -> const char * kAssertStr;
}

// Range: 0x80539474 -> 0x8053948C
void JoinRequestMsg::GetAuthenticationData(const class JoinRequestMsg * const this /* r5 */) {}

// Range: 0x8053948C -> 0x805395B4
void JoinRequestMsg::Save(const class JoinRequestMsg * const this /* r30 */, class BinStream & dest /* r31 */) {
    // Local variables
    unsigned char numPlayers; // r29
    int n; // r28
}

// Range: 0x805395B4 -> 0x80539934
void JoinRequestMsg::Load(class JoinRequestMsg * const this /* r28 */, class BinStream & src /* r29 */) {
    // Local variables
    unsigned char numPlayers; // r1+0x39
    int n; // r30
    unsigned char playerID; // r1+0x38
    int playerDataSize; // r1+0x44
    class MemStream playerBuffer; // r1+0x48
    int authDataSize; // r1+0x40

    // References
    // -> const char * gStlAllocName;
    // -> struct [anonymous] __RTTI__Pc;
    // -> unsigned char gStlAllocNameLookup;
    // -> struct [anonymous] __vt__9MemStream;
    // -> struct [anonymous] __vt__9BinStream;
}

// Range: 0x80539934 -> 0x80539968
void * JoinResponseMsg::JoinResponseMsg() {
    // References
    // -> struct [anonymous] __vt__15JoinResponseMsg;
}

// Range: 0x80539968 -> 0x80539978
unsigned char JoinResponseMsg::Joined() {}

// Range: 0x80539978 -> 0x80539A48
void JoinResponseMsg::SetNewPlayerID(class JoinResponseMsg * const this /* r31 */, int oldID /* r1+0x8 */, int newID /* r1+0xC */) {}

// Range: 0x80539A48 -> 0x80539A98
void JoinResponseMsg::SwapOldIDs() {
    // Local variables
    int n; // r8
}

// Range: 0x80539A98 -> 0x80539B74
void JoinResponseMsg::Save(const class JoinResponseMsg * const this /* r27 */, class BinStream & dest /* r28 */) {
    // Local variables
    int numIDs; // r30
    int n; // r29
}

// Range: 0x80539B74 -> 0x80539CC0
void JoinResponseMsg::Load(class JoinResponseMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int error; // r1+0x1C
    int numIDs; // r1+0x18
    int n; // r31
    int oldID; // r1+0x14
    int newID; // r1+0x10
}

// Range: 0x80539CC0 -> 0x80539D34
void * NewPlayerMsg::NewPlayerMsg(class NewPlayerMsg * const this /* r30 */, const class User * newPlayer /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12NewPlayerMsg;
}

// Range: 0x80539D34 -> 0x80539D4C
void NewPlayerMsg::GetUser(const class NewPlayerMsg * const this /* r5 */) {}

// Range: 0x80539D4C -> 0x80539DC4
void NewPlayerMsg::Save(const class NewPlayerMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x80539DC4 -> 0x80539E94
void NewPlayerMsg::Load(class NewPlayerMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int numBytes; // r1+0x10
}

// Range: 0x80539E94 -> 0x80539EA8
void * PlayerLeftMsg::PlayerLeftMsg() {
    // References
    // -> struct [anonymous] __vt__13PlayerLeftMsg;
}

// Range: 0x80539EA8 -> 0x80539EE0
void PlayerLeftMsg::Save(const class PlayerLeftMsg * const this /* r5 */) {}

// Range: 0x80539EE0 -> 0x80539EF4
void PlayerLeftMsg::Load(class PlayerLeftMsg * const this /* r5 */) {}

// Range: 0x80539EF4 -> 0x80539F98
void * AddPlayerRequestMsg::AddPlayerRequestMsg(class AddPlayerRequestMsg * const this /* r30 */, const class User * newPlayer /* r31 */) {
    // References
    // -> class Net TheNet;
    // -> struct [anonymous] __vt__19AddPlayerRequestMsg;
}

// Range: 0x80539F98 -> 0x80539FB0
void AddPlayerRequestMsg::GetUser(const class AddPlayerRequestMsg * const this /* r5 */) {}

// Range: 0x80539FB0 -> 0x80539FC8
void AddPlayerRequestMsg::GetAuthenticationData(const class AddPlayerRequestMsg * const this /* r5 */) {}

// Range: 0x80539FC8 -> 0x8053A06C
void AddPlayerRequestMsg::Save(const class AddPlayerRequestMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053A06C -> 0x8053A1C0
void AddPlayerRequestMsg::Load(class AddPlayerRequestMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int numBytes; // r1+0x18
}

// Range: 0x8053A1C0 -> 0x8053A248
void AddPlayerResponseMsg::Save(const class AddPlayerResponseMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053A248 -> 0x8053A2C4
void AddPlayerResponseMsg::Load(class AddPlayerResponseMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x8053A2C4 -> 0x8053A348
void * ChangePlayerMsg::ChangePlayerMsg(class ChangePlayerMsg * const this /* r29 */, const class User * playerData /* r30 */, unsigned int dirtyMask /* r31 */) {
    // References
    // -> struct [anonymous] __vt__15ChangePlayerMsg;
}

// Range: 0x8053A348 -> 0x8053A360
void ChangePlayerMsg::GetUser(const class ChangePlayerMsg * const this /* r5 */) {}

// Range: 0x8053A360 -> 0x8053A3F0
void ChangePlayerMsg::Save(const class ChangePlayerMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053A3F0 -> 0x8053A4D0
void ChangePlayerMsg::Load(class ChangePlayerMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int numBytes; // r1+0x10
}

// Range: 0x8053A4D0 -> 0x8053A4E4
void * FinishedLoadingMsg::FinishedLoadingMsg() {
    // References
    // -> struct [anonymous] __vt__18FinishedLoadingMsg;
}

// Range: 0x8053A4E4 -> 0x8053A51C
void FinishedLoadingMsg::Save(const class FinishedLoadingMsg * const this /* r5 */) {}

// Range: 0x8053A51C -> 0x8053A530
void FinishedLoadingMsg::Load(class FinishedLoadingMsg * const this /* r5 */) {}

// Range: 0x8053A530 -> 0x8053A548
void * StartGameOnTimeMsg::StartGameOnTimeMsg() {
    // References
    // -> struct [anonymous] __vt__18StartGameOnTimeMsg;
}

// Range: 0x8053A548 -> 0x8053A588
void StartGameOnTimeMsg::Save(const class StartGameOnTimeMsg * const this /* r5 */) {}

// Range: 0x8053A588 -> 0x8053A59C
void StartGameOnTimeMsg::Load(class StartGameOnTimeMsg * const this /* r5 */) {}

// Range: 0x8053A59C -> 0x8053A5B4
void * EndGameMsg::EndGameMsg() {
    // References
    // -> struct [anonymous] __vt__10EndGameMsg;
}

// Range: 0x8053A5B4 -> 0x8053A618
void EndGameMsg::Save(const class EndGameMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053A618 -> 0x8053A680
void EndGameMsg::Load(class EndGameMsg * const this /* r30 */, class BinStream & src /* r31 */) {}

// Range: 0x8053A680 -> 0x8053A698
void VoiceDataMsg::GetVoiceData(const class VoiceDataMsg * const this /* r5 */) {}

// Range: 0x8053A698 -> 0x8053A710
void VoiceDataMsg::Save(const class VoiceDataMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053A710 -> 0x8053A7E0
void VoiceDataMsg::Load(class VoiceDataMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int numBytes; // r1+0x10
}

// Range: 0x8053A7E0 -> 0x8053A84C
void * DataArrayMsg::DataArrayMsg(class DataArrayMsg * const this /* r30 */, class DataArray * dataArray /* r31 */) {
    // References
    // -> struct [anonymous] __vt__12DataArrayMsg;
}

// Range: 0x8053A84C -> 0x8053A8B4
void DataArrayMsg::Save(const class DataArrayMsg * const this /* r30 */, class BinStream & dest /* r31 */) {}

// Range: 0x8053A8B4 -> 0x8053A974
void DataArrayMsg::Load(class DataArrayMsg * const this /* r29 */, class BinStream & src /* r30 */) {
    // Local variables
    int numBytes; // r1+0x10
}

// Range: 0x8053A974 -> 0x8053A9FC
void DataArrayMsg::Dispatch() {
    // Local variables
    class DataArray * msg; // r1+0x8
}

// Range: 0x8053A9FC -> 0x8053AADC
void DataArrayMsg::Print(const class DataArrayMsg * const this /* r30 */, class TextStream & text /* r31 */) {
    // Local variables
    class MemStream newBuffer; // r1+0x10
    class DataArray * msg; // r1+0xC
}

struct {
    // total size: 0x28
} __vt__12DataArrayMsg; // size: 0x28, address: 0x80907E70
struct {
    // total size: 0x8
} __RTTI__12DataArrayMsg; // size: 0x8, address: 0x80907EB8
struct {
    // total size: 0x28
} __vt__12VoiceDataMsg; // size: 0x28, address: 0x80907EC0
struct {
    // total size: 0x28
} __vt__10EndGameMsg; // size: 0x28, address: 0x80907EE8
struct {
    // total size: 0x28
} __vt__18StartGameOnTimeMsg; // size: 0x28, address: 0x80907F10
struct {
    // total size: 0x28
} __vt__18FinishedLoadingMsg; // size: 0x28, address: 0x80907F38
struct {
    // total size: 0x28
} __vt__15ChangePlayerMsg; // size: 0x28, address: 0x80907F60
struct {
    // total size: 0x28
} __vt__20AddPlayerResponseMsg; // size: 0x28, address: 0x80907F88
struct {
    // total size: 0x28
} __vt__19AddPlayerRequestMsg; // size: 0x28, address: 0x80907FB0
struct {
    // total size: 0x28
} __vt__13PlayerLeftMsg; // size: 0x28, address: 0x80907FD8
struct {
    // total size: 0x28
} __vt__12NewPlayerMsg; // size: 0x28, address: 0x80908000
struct {
    // total size: 0x28
} __vt__15JoinResponseMsg; // size: 0x28, address: 0x80908028
struct {
    // total size: 0x28
} __vt__14JoinRequestMsg; // size: 0x28, address: 0x80908050
struct {
    // total size: 0x8
} __RTTI__P9MemStream; // size: 0x8, address: 0x80908088

