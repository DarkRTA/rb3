#ifndef BANDOBJ_BANDLABEL_H
#define BANDOBJ_BANDLABEL_H

#include "obj/ObjMacros.h"
#include "ui/UILabel.h"

class BandLabel : public UILabel {
    public:
    BandLabel();
    OBJ_CLASSNAME(BandLabel)
    OBJ_SET_TYPE(BandLabel)
};

#endif // BANDOBJ_BANDLABEL_H
