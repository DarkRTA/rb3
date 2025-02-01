#include "meta/MemcardMgr_Wii.h"

MemcardMgr TheMemcardMgr;

MemcardMgr::MemcardMgr()
    : unka4(0), unka8(0), unkac(0), unkb9(0), unkbc(-1), unkc0(0), unkcc(0), unkd0(0),
      unkd4(-1), unkd8(-1), unkdc(0) {}

MemcardMgr::~MemcardMgr() {}