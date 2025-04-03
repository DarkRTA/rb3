#ifndef PLATFORM_EXCEPTIONHANDLER_H
#define PLATFORM_EXCEPTIONHANDLER_H

namespace Quazal {
    class ExceptionHandler {
    public:
        static void CheckCrtExceptions();
        void Initialize();
    };
}

#endif
