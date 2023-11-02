#include "syncobjmsg.hpp"
#include "binstream.hpp"
#include "string.hpp"
#include "memstream.hpp"
#include "message.hpp"

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

// fn_800B7D98
Message::Message(Symbol s, const DataNode& dn1, const DataNode& dn2, const DataNode& dn3){
    DataArray* da = DataArray::fn_8035CF9C(0x10, 0x10, 1);
	if(da != 0) da = new DataArray(4);
	unk4 = da;

	unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
    unk4->GetNodeAtIndex(2)->operator=(dn1);
    unk4->GetNodeAtIndex(3)->operator=(dn2);
    unk4->GetNodeAtIndex(4)->operator=(dn3);
}