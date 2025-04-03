#pragma once
#include "Platform/RootObject.h"

namespace Quazal {
    class PluginObject : public RootObject {
    public:
        PluginObject() : unk4(0) {}
        virtual ~PluginObject() {}

        int unk4; // Plugin* mPlugin
    };
}