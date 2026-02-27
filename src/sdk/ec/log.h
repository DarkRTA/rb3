#ifndef EC_LOG_H
#define EC_LOG_H

#include <ec/result.h>

enum ECLogLevel {
    ECLogLevel_Error = 1,
    ECLogLevel_Warning = 2,
    ECLogLevel_Info = 3,
    ECLogLevel_Fine = 4,
    ECLogLevel_Finer = 5,
    ECLogLevel_Finest = 6,
};

namespace ec {
    long lovBufLevel;
    long logLevel;
    void logmsg(long level, const char* format, ...);
    ECResult setLogLevel(long level);

}

#endif
