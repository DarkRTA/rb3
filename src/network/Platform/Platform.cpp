#include "Platform.h"

#include "Platform/HighResolutionClock.h"
#include "Platform/SystemError.h"
#include "revolution/os/OSThread.h"
#include "revolution/os/OSTime.h"

char* g_szGeneralErrorDescriptions[29] = {
    "Insufficient Memory",
    "Illegal Memory Access",
    "Win32 function returned an error" ,
    "Index out of bound",
    "Duplicated key within the collection",
    "The item was in use, and could not be deleted",
    "The item was not found",
    "An access beyond the end of the collection has occured",
    "Object not initialized",
    "Feature not implemented",
    "IDGenerator is out of ID" ,
    "Internal Exception",
    "Timeout occured",
    "Child process could not be launched",
    "Invalid operation",
    "Multiple instances not allowed",
    "Multiple exception handlers not allowed",
    "This product has expired",
    "Parameter out of range",
    "Assertion Failed",
    "Deadlock detected",
    "NetZ has not been initialized",
    "Invalid parameter",
    "IO error",
    "Product key does not exist or is invalid",
    "Buffer extraction overflow",
    "Invalid wait",
    "Access denied",
    "Operation denied"
};  
namespace Quazal {
    Platform* Platform::_Instance;
    RandomNumberGenerator Platform::s_oRNG;
    ErrorDescriptionTable Platform::m_oErrorTable(g_szGeneralErrorDescriptions, 0);

    Platform* Platform::CreateInstance() {
        Platform* ptfm = new (__FILE__, 137) Platform;
        if (ptfm != NULL) {
            _Instance = ptfm;
            HighResolutionClock hr;
            Time& tim = hr.GetTime();
            s_oRNG.SetRandomNumberSeed(tim);
        }
        return _Instance = ptfm;
    }

    void Platform::DeleteInstance() {
        if (_Instance) delete _Instance;
    }

    u32 Platform::GetRandomNumber(unsigned int ui) {
        return s_oRNG.GetRandomNumber(ui);
    }

    float Platform::GetRealRandomNumber(float f) {
        return s_oRNG.GetRealRandomNumber(f);
    }

    void Platform::Breakpoint() {

    }

    void Platform::Sleep(uint msecs) {
        if (msecs != 0) {
            OSSleepTicks(OSMillisecondsToTicks(msecs));
        } else OSYieldThread();
    }
}
