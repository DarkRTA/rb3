#ifndef METROTRK_DISPATCH
#define METROTRK_DISPATCH

#include "MetroTRK/trk.h"
#include "MetroTRK/msgbuf.h"

#ifdef __cplusplus
extern "C"{
#endif

DSError TRK_DispatchMessage(MessageBuffer*);

#ifdef __cplusplus
}
#endif
#endif
