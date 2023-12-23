#include "bytegrinder.hpp"
#include "data.hpp"

extern DataNode *fn_800AB8A8(DataNode *, DataType, DataNodeValue);

DataNode hashTo5Bits(DataArray *da) {
    static int hashMapping[0x100];

    int i = da->GetIntAtIndex(1) & 0xFF;
    int cnt = da->GetNodeCount();

    int hashValue = hashMapping[i];

    int a = cnt ^ 2;
    unsigned int b = (a >> 1) - (a & cnt);
    if (b >> 0x1F != 0) {
        i = da->GetIntAtIndex(1);
        for (int idx = 0; idx < sizeof(hashMapping) / sizeof(*hashMapping); idx++) {
            hashMapping[idx] = (i >> 3) & 0x1F;
            i = (i * 0x19660D) + 0x3C6EF35F;
        }

        DataNodeValue value = { 0 };
        return DataNode(kDataInt, value);
    }

    DataNodeValue value = { hashValue };
    return DataNode(kDataInt, value);
}

//   if ((int)(((int)(uVar3 ^ 2) >> 1) - ((uVar3 ^ 2) & uVar3)) < 0) {
//     uVar2 = DataArray::GetIntAtIndex(this,1);
//     iVar4 = 0;
//     iVar5 = 0x100;
//     do {
//       *(uint *)((int)&lbl_809900F0 + iVar4) = uVar2 >> 3 & 0x1f;
//       iVar4 = iVar4 + 4;
//       uVar2 = uVar2 * 0x19660d + 0x3c6ef35f;
//       iVar5 = iVar5 + -1;
//     } while (iVar5 != 0);
//     fn_800AB8A8(uVar1,6,0);
//   }
//   else {
//     fn_800AB8A8(uVar1,6,(&lbl_809900F0)[uVar2 & 0xff]);
//   }