#ifndef META_HAQMANAGER_H
#define META_HAQMANAGER_H
#include "obj/Object.h"
#include "utl/Str.h"

enum HAQType {
    kHAQType_Screen,
    kHAQType_Focus,
    kHAQType_Button,
    kHAQType_Slider,
    kHAQType_List,
    kHAQType_Song,
    kHAQType_Checkbox
};

class HAQManager : public Hmx::Object {
public:
    HAQManager();
    virtual ~HAQManager();
    virtual DataNode Handle(DataArray*, bool);

    String GetLabelForType(HAQType) const;
    static void Init();

    bool m_bEnabled;
};

extern HAQManager* TheHAQMgr;

#endif
