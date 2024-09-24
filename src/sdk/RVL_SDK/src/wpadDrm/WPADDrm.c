#include "WPADDrm.h"
#include <revolution/OS.h>

const char* __WPADDrmVersion = "<< RVL_SDK - WPADDrm \trelease build: Dec 22 2009 01:21:35 (0x4302_145) >>";

void (*_wpadDRMInit)(void) = WPADDrumInit;
int _enabledDRM = 1;

void WPADDrumInit(void) {
    OSRegisterVersion(__WPADDrmVersion);
}
