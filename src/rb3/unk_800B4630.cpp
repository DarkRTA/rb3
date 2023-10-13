#include "syncobjmsg.hpp"
#include "binstream.hpp"
#include "string.hpp"
#include "memstream.hpp"

extern int fn_800A9C78(MemStream*);

// fn_800BA7E0
void SyncObjMsg::Save(BinStream& bs) const {
    bs << tag;
    bs.WriteEndian4(dirty_mask);
    bs.WriteEndian4(fn_800A9C78(unk14));
    fn_800BA788(bs);
}

// fn_800BA84C
void SyncObjMsg::Load(BinStream& bs){
    unsigned int ui;
    bs >> tag;
    bs.ReadEndian4(&dirty_mask);
    bs.ReadEndian4(&ui);
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