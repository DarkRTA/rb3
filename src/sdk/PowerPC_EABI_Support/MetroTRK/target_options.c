#include "types.h"
u8 bUseSerialIO;

void SetUseSerialIO(u8 b) {
	bUseSerialIO = b;
}

u8 GetUseSerialIO() {
	return bUseSerialIO;
}
