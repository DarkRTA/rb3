#include "Adjacency.h"

Adjacencies::Adjacencies() : mNbEdges(0), mCurrentNbFaces(0), mEdges(0), mNbFaces(0), mFaces(0) {

}

Adjacencies::~Adjacencies(){
    delete [] mEdges;
    mEdges = 0;
    delete [] mFaces;
    mFaces = 0;
}

bool Adjacencies::Init(ADJACENCIESCREATE& create){
    mNbFaces = create.NbFaces;
    mFaces = new AdjTriangle[mNbFaces];
    if(mFaces == 0) return false;
    else {
        mEdges = new AdjEdge[mNbFaces * 3];
        if(mEdges == 0) return false;
        else {
            for(int i = 0; i < mNbFaces; i++){
                unsigned int ref0, ref1, ref2;
                if(create.DFaces != 0){
                    ref0 = *create.DFaces;
                }
                else ref0 = 0;
                if(create.DFaces == 0){
                    if(mEdges == 0) ref1 = 1;
                    else ref1 = mEdges[i].Ref1;
                }
                else ref1 = mEdges[mNbFaces * 3].Ref1;
                if(create.DFaces == 0){
                    if(mEdges == 0) ref2 = 2;
                    else ref2 = mEdges[i].FaceNb;
                }
                else ref2 = mEdges[mNbFaces * 3].FaceNb;
                AddTriangle(ref0, ref1, ref2);
            }
            return true;
        }
        
    }
}

bool Adjacencies::AddTriangle(unsigned int ref0, unsigned int ref1, unsigned int ref2){
    mFaces[mCurrentNbFaces].VRef[0] = ref0;
    mFaces[mCurrentNbFaces].VRef[1] = ref1;
    mFaces[mCurrentNbFaces].VRef[2] = ref2;
    mFaces[mCurrentNbFaces].ATri[0] = -1;
    mFaces[mCurrentNbFaces].ATri[1] = -1;
    mFaces[mCurrentNbFaces].ATri[2] = -1;
    if(ref0 < ref1) AddEdge(ref0, ref1, mCurrentNbFaces);
    else AddEdge(ref1, ref0, mCurrentNbFaces);
    if(ref0 < ref2) AddEdge(ref0, ref2, mCurrentNbFaces);
    else AddEdge(ref2, ref0, mCurrentNbFaces);
    if(ref1 < ref2) AddEdge(ref1, ref2, mCurrentNbFaces);
    else AddEdge(ref2, ref1, mCurrentNbFaces);
    mCurrentNbFaces++;
    return true;
}

bool Adjacencies::AddEdge(unsigned int ref0, unsigned int ref1, unsigned int ref2){
    mEdges[mNbEdges].Ref0 = ref0;
    mEdges[mNbEdges].Ref1 = ref1;
    mEdges[mNbEdges].FaceNb = ref2;
    mNbEdges++;
    return true;
}

bool Adjacencies::UpdateLink(unsigned int firsttri, unsigned int secondtri, unsigned int ref0, unsigned int ref1){
    AdjTriangle* tri1 = &mFaces[firsttri];
    AdjTriangle* tri2 = &mFaces[secondtri];
    unsigned int edge = tri1->FindEdge(ref0, ref1);
    if((edge & 0xFF) == 0xFF) return false;
    else {
        unsigned int edge2 = tri2->FindEdge(ref0, ref1);
        if((edge2 & 0xFF) == 0xFF) return false;
        else {
            tri1->ATri[edge & 0xFF] = secondtri | (edge2 << 0x1E);
            tri2->ATri[edge2 & 0xFF] = firsttri | (edge << 0x1E);
            return true;
        }
    }
}

// undefined4 __thiscall
// Adjacencies::UpdateLink(Adjacencies *this,uint param_1,uint param_2,uint param_3,uint param_4)

// {
//   uint uVar1;
//   undefined4 uVar2;
//   uint uVar3;
//   AdjTriangle *this_00;
//   AdjTriangle *this_01;
  
//   this_01 = (AdjTriangle *)(*(int *)(this + 0x10) + param_1 * 0x18);
//   this_00 = (AdjTriangle *)(*(int *)(this + 0x10) + param_2 * 0x18);
//   uVar1 = AdjTriangle::FindEdge(this_01,param_3,param_4);
//   if ((uVar1 & 0xff) == 0xff) {
//     uVar2 = 0;
//   }
//   else {
//     uVar3 = AdjTriangle::FindEdge(this_00,param_3,param_4);
//     if ((uVar3 & 0xff) == 0xff) {
//       uVar2 = 0;
//     }
//     else {
//       *(uint *)(this_01 + (uVar1 & 0xff) * 4 + 0xc) = param_2 | uVar3 << 0x1e;
//       *(uint *)(this_00 + (uVar3 & 0xff) * 4 + 0xc) = param_1 | uVar1 << 0x1e;
//       uVar2 = 1;
//     }
//   }
//   return uVar2;
// }

unsigned int AdjTriangle::FindEdge(unsigned int ui1, unsigned int ui2){
    unsigned int edge = 0xFF;
    if(VRef[0] == ui1 && VRef[1] == ui2) edge = 0;
    else if(VRef[0] == ui2 && VRef[1] == ui1) edge = 0;
    else if(VRef[0] == ui1 && VRef[2] == ui2) edge = 1;
    else if(VRef[0] == ui2 && VRef[2] == ui1) edge = 1;
    else if(VRef[1] == ui1 && VRef[2] == ui2) edge = 2;
    else if(VRef[1] == ui2 && VRef[2] == ui1) edge = 2;
    return edge;
}

unsigned int AdjTriangle::OppositeVertex(unsigned int ui1, unsigned int ui2){
    unsigned int vert = -1;
    if(VRef[0] == ui1 && VRef[1] == ui2) vert = VRef[2];
    else if(VRef[0] == ui2 && VRef[1] == ui1) vert = VRef[2];
    else if(VRef[0] == ui1 && VRef[2] == ui2) vert = VRef[1];
    else if(VRef[0] == ui2 && VRef[2] == ui1) vert = VRef[1];
    else if(VRef[1] == ui1 && VRef[2] == ui2) vert = VRef[0];
    else if(VRef[1] == ui2 && VRef[2] == ui1) vert = VRef[0];

    return vert;
}
