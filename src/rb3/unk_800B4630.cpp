#include "syncobjmsg.hpp"
#include "binstream.hpp"
#include "string.hpp"
#include "memstream.hpp"

// fn_800B95C4
BinStream* BinStream::WriteFloat(float f){
    WriteEndian(&f, 4);
    return this;
}

extern int fn_800A9C78(MemStream*);

// fn_800BA7E0
void SyncObjMsg::Save(BinStream& bs) const {
    bs << tag;
    bs.WriteWord(dirty_mask);
    bs.WriteWord(fn_800A9C78((MemStream*)(&unk14)));
    fn_800BA788(bs);
}

// fn_800BA84C
void SyncObjMsg::Load(BinStream& bs){
    unsigned int ui;
    bs >> tag;
    bs.ReadWord(&dirty_mask);
    bs.ReadWord(&ui);
}

extern char lbl_8082C43C[];
extern char* fn_800BAA2C(char*, String, unsigned int);

// fn_800BA9BC
void SyncObjMsg::Print(TextStream& ts) const {
    ts << fn_800BAA2C(lbl_8082C43C + 0x82, tag, dirty_mask); // "SyncObj tag = %s, dirtyMask = %x\n"
}

// fn_800BB518
int MemStream::Tell(){
    return pos;
}