#include "ui/Utl.h"

bool IsNavAction(JoypadAction act){
    return act == kAction_Up || act == kAction_Down;
}