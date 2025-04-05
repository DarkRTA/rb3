#include "network/Core/WorkerThreads.h"

namespace Quazal {
    WorkerThreads::WorkerThreads() : m_csState(0x40000000) { m_eState = 2; }
    WorkerThreads::~WorkerThreads() { Stop(); }
}