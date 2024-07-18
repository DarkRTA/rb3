#include "WPADGtr.h"
#include "revolution/OS.h"

const char* __WPADGtrVersion = "<< RVL_SDK - WPADGtr \trelease build: Dec 22 2009 01:21:33 (0x4302_145) >>";

void (*_wpadGTRInit)(void) = WPADGuitarInit;
int _enabledGTR = 1;

void WPADGuitarInit(void) {
    OSRegisterVersion(__WPADGtrVersion);
}
