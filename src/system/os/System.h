#pragma once
#include "obj/Data.h"
#include "utl/Symbol.h"
#include <vector>
#include "os/Platform.h"

extern const char *gNullStr;
extern std::vector<char *> TheSystemArgs;
extern const char *gHostFile;
extern bool gHostCached;

enum GfxMode {
    kOldGfx = 0,
    kNewGfx = 1,
};

void SetGfxMode(GfxMode);
GfxMode GetGfxMode();

static DataNode OnSystemLanguage(DataArray *);
static DataNode OnSystemExec(DataArray *);
static DataNode OnUsingCD(DataArray *);
static DataNode OnSupportedLanguages(DataArray *);

inline bool IsVertexCompressionSupported(Platform p) {
    return p == kPlatformXBox || p == kPlatformPS3;
}

Symbol PlatformSymbol(Platform);
bool PlatformLittleEndian(Platform);
Platform ConsolePlatform();

void StripEditorData();
bool UsingCD();
void SetUsingCD(bool);

DataArray *SystemConfig();
DataArray *SystemConfig(Symbol);
DataArray *SystemConfig(Symbol, Symbol);
DataArray *SystemConfig(Symbol, Symbol, Symbol);
DataArray *SystemConfig(Symbol, Symbol, Symbol, Symbol);
DataArray *SystemConfig(Symbol, Symbol, Symbol, Symbol, Symbol);

Symbol SystemLanguage();
DataArray *SupportedLanguages(bool);
bool IsSupportedLanguage(Symbol, bool);
Symbol GetSystemLanguage(Symbol);
void SetSystemLanguage(Symbol, bool);

int SystemExec(const char *);
int SystemMs();
void SystemPoll(bool pollTasks);
void SetSystemArgs(int, char **);
void SystemPreInit(int, char **, const char *);
void SystemPreInit(const char *);

void CaptureStackTrace(int depth, unsigned int *trace);
void AppendStackTrace(char *msg);
void AppendThreadStackTrace(char *msg, unsigned int *trace);

bool PlatformDebugBreak();
