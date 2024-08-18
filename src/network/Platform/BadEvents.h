#pragma once
namespace Quazal {
    class BadEvents {
        enum _ID {

        };

        static void Signal(_ID);
        static int* s_pInstance;
    };
}