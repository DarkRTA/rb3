#include "messages/stringstoppedmsg.hpp"
#include "obj/Data.h"

// fn_80313FB0
Symbol StringStoppedMsg::Type() {
    static Symbol t("string_stopped");
    return t;
}
