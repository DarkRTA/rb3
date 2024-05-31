#include "char/CharTaskMgr.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"

#include "decomp.h"

bool CharTaskMgr::sShowGraph = false;

namespace {
    static DataNode OnToggleCharTaskGraph(DataArray* arr){
        CharTaskMgr::sShowGraph = !CharTaskMgr::sShowGraph;
        return DataNode(CharTaskMgr::sShowGraph);
    }
}

void CharTaskMgr::Init(){
    DataRegisterFunc("toggle_char_task_graph", OnToggleCharTaskGraph);
}

DECOMP_FORCEACTIVE(CharTaskMgr,
    "<unknown>",
    "%s: %g",
    "%g %g %f %x",
    "%d) start %.3f end %.3f pri %.3f\n"
)
