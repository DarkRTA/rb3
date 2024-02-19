#include "utl/SysTest.h"

void LogColumnInfo(TextStream* ts, DataArray* da, bool b){
    const char* sep = b ? "," : ";";
    *ts << "Category" << sep << "CategoryName" << sep << "Column" << sep << "Budget" << sep << "BudgetType" << sep << "AlwaysShow" << sep << "Tooltip\n";
}

// void LogColumnInfo(TextStream *param_1,DataArray *param_2,bool param_3)

// {
//   TextStream *pTVar1;
//   DataNode *pDVar2;
//   DataArray *this;
//   char *__s;
//   char *pcVar3;
//   int iVar4;
//   int iVar5;
//   char *pcVar6;
//   char *pcVar7;
//   undefined3 in_register_00000014;
//   int iVar8;
//   char *pcVar9;
//   double dVar10;
  
//   pcVar9 = s_,_80bdb6da;
//   if (CONCAT31(in_register_00000014,param_3) != 0) {
//     pcVar9 = @stringBase0;
//   }
//   pTVar1 = (TextStream *)TextStream::operator_<<(param_1,s_Category_80bdb6dc);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,s_CategoryName_80bdb6e5);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,s_Column_80bdb6f2);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,s_Budget_80bdb6f9);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,s_BudgetType_80bdb700);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,s_AlwaysShow_80bdb70b);
//   pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//   TextStream::operator_<<(pTVar1,s_Tooltip_80bdb716);
//   for (iVar8 = 1; iVar8 < *(short *)(param_2 + 8); iVar8 = iVar8 + 1) {
//     pDVar2 = (DataNode *)DataArray::Node(param_2,iVar8);
//     this = (DataArray *)DataNode::Array(pDVar2,param_2);
//     pDVar2 = (DataNode *)DataArray::Node(this,5);
//     __s = (char *)DataNode::Str(pDVar2,this);
//     pcVar3 = strchr(__s,0x2c);
//     if (pcVar3 != (char *)0x0) {
//       pcVar3 = MakeString(s_Tooltip_"%s"_may_not_contain_com_80bdb71f,__s);
//       Debug::Fail((Debug *)TheDebug,pcVar3);
//     }
//     pDVar2 = (DataNode *)DataArray::Node(this,4);
//     iVar4 = DataNode::Int(pDVar2,this);
//     pDVar2 = (DataNode *)DataArray::Node(this,3);
//     iVar5 = DataNode::Int(pDVar2,this);
//     pDVar2 = (DataNode *)DataArray::Node(this,2);
//     dVar10 = (double)DataNode::Float(pDVar2,this);
//     pDVar2 = (DataNode *)DataArray::Node(this,1);
//     pcVar3 = (char *)DataNode::Str(pDVar2,this);
//     pDVar2 = (DataNode *)DataArray::Node(this,0);
//     pcVar6 = (char *)DataNode::Str(pDVar2,this);
//     pcVar7 = MakeString(s_%.3f_80bdb74f,(float)dVar10);
//     pTVar1 = (TextStream *)TextStream::operator_<<(param_1,s_column_info_80bdb743);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar6);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar3);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar7);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,iVar5);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,iVar4);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,pcVar9);
//     pTVar1 = (TextStream *)TextStream::operator_<<(pTVar1,__s);
//     TextStream::operator_<<(pTVar1,s__80bdb754);
//   }
//   TextStream::operator_<<(param_1,s__80bdb754);
//   return;
// }
