#ifndef RB3_DOFPROC_HPP
#define RB3_DOFPROC_HPP
#include "hmx/object.hpp"

class DOFProc : public Hmx::Object {
public:
    DOFProc();
    virtual ~DOFProc();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);

    static Symbol StaticClassName();
    static DOFProc* Params();
    static void Terminate();
    static DOFProc* NewDOFProc();
    static void Init();
};

#endif
