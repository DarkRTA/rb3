#ifndef RB3_PLATFORMMGR_HPP
#define RB3_PLATFORMMGR_HPP
#include "msgsource.hpp"

class PlatformMgr : public MsgSource {
public:
    PlatformMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~PlatformMgr();
    
    void SetUnkCE55(bool);

    bool unknowns[0xCE39];
    bool unkCE55;
};

#endif
