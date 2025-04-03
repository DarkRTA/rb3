#include "network/Plugins/Stream.h"

namespace Quazal {
    PseudoGlobalVariable<StreamSettings> Stream::s_oStreamSettings[16];

    Stream::Stream(Type t) : mType(t) {}
    Stream::~Stream() {}
}