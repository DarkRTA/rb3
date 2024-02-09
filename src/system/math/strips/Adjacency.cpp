#include "Adjacency.h"

Adjacencies::Adjacencies() : mNbEdges(0), mCurrentNbFaces(0), mEdges(0), mNbFaces(0), mFaces(0) {

}

Adjacencies::~Adjacencies(){
    delete [] &mFaces->VRef;
    delete [] &mFaces->ATri;
}
