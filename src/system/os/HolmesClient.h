#ifndef OS_HOLMESCLIENT_H
#define OS_HOLMESCLIENT_H

void HolmesClientInit();
void HolmesClientTerminate();

bool UsingHolmes(int);

unsigned int HolmesResolveIP();

#endif
