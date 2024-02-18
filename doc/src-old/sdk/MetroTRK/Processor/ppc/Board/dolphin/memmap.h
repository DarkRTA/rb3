#ifndef METROTRK_MEM_TRK_H
#define METROTRK_MEM_TRK_H
#include "MetroTRK/dstypes.h"
#include "MetroTRK/trk.h"

typedef struct memRange{
	ui8* start;
	ui8* end;
	bool readable;
	bool writeable;
} memRange;


const memRange gTRKMemMap[1] = {{
	(ui8*)0,
	(ui8*)-1,
	true,
	true
}};


#endif
