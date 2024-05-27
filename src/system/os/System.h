#ifndef OS_SYSTEM_H
#define OS_SYSTEM_H
#include "obj/Data.h"
#include "utl/Symbol.h"
#include <vector>

extern const char* gNullStr;
extern std::vector<char*> TheSystemArgs;
extern const char* gHostFile;
extern bool gHostCached;

enum GfxMode {
    kOldGfx = 0,
    kNewGfx = 1,
};

void SetGfxMode(GfxMode);
GfxMode GetGfxMode();

static DataNode OnSystemLanguage(DataArray*);
static DataNode OnSystemExec(DataArray*);
static DataNode OnUsingCD(DataArray*);
static DataNode OnSupportedLanguages(DataArray*);

enum Platform {
    kPlatformNone = 0,
    kPlatformPS2 = 1,
    kPlatformXBox = 2,
    kPlatformPC = 3,
    kPlatformPS3 = 4,
    kPlatformWii = 5,
};

Symbol PlatformSymbol(Platform);
bool PlatformLittleEndian(Platform);
Platform ConsolePlatform();

void StripEditorData();
bool UsingCD();
void SetUsingCD(bool);

DataArray* SystemConfig();
DataArray* SystemConfig(Symbol);
DataArray* SystemConfig(Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol, Symbol);
DataArray* SystemConfig(Symbol, Symbol, Symbol, Symbol, Symbol);

Symbol SystemLanguage();
DataArray* SupportedLanguages(bool);
bool IsSupportedLanguage(Symbol, bool);
Symbol GetSystemLanguage(Symbol);
void SetSystemLanguage(Symbol, bool);

int SystemExec(const char*);
int SystemMs();
void SystemPoll(bool pollTasks);
void SetSystemArgs(int, char**);
void SystemPreInit(int, char**, const char*);
void SystemPreInit(const char*);

// System_Wii
void CaptureStackTrace(int depth, unsigned int* trace);
bool PlatformDebugBreak();

#endif
