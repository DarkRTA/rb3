#include "message.hpp"
#include "symbol.hpp"
#include "data.hpp"
#include "common.hpp"

extern DataArray* fn_8035CF9C(int, int, int);

// fn_80177AD4
Message::Message(Symbol s, const DataNode& dn1, const DataNode& dn2, const DataNode& dn3, const DataNode& dn4){
    unk4 = new (fn_8035CF9C(0x10, 0x10, 1)) DataArray(6);
	unk4->GetNodeAtIndex(1)->operator=(DataNode(s));
    unk4->GetNodeAtIndex(2)->operator=(dn1);
    unk4->GetNodeAtIndex(3)->operator=(dn2);
    unk4->GetNodeAtIndex(4)->operator=(dn3);
    unk4->GetNodeAtIndex(5)->operator=(dn4);
}