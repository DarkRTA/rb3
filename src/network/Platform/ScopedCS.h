#ifndef PLATFORM_SCOPEDCS_H
#define PLATFORM_SCOPEDCS_H
#include "Platform/CriticalSection.h"
#include "Platform/RootObject.h"
#include "Platform/MutexPrimitive.h"

namespace Quazal {
    class ScopedCS : public RootObject {
    public:
        ScopedCS(CriticalSection& cs) : unk0(true), critSec(&cs) {
            if(!MutexPrimitive::s_bNoOp) critSec->EnterImpl();
        }

        ~ScopedCS(){ 
            EndScope(); 
        }

        void EndScope(){
            if(unk0){
                if(!MutexPrimitive::s_bNoOp) critSec->LeaveImpl();
                unk0 = false;
            }
        }
        
        bool unk0;
        CriticalSection* critSec;
    };
}

#endif
