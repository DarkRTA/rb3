#pragma once
#ifdef __cplusplus
extern "C" {
#endif

int DWC_CheckProfanityAsync(const unsigned short ** words, int wordsnum, const char * reserved, int timeout, char * result, int * badwordsnum);
int DWC_CheckProfanityProcess();

#ifdef __cplusplus
}
#endif
