#pragma once

#include "Platform/RefCountedObject.h"

namespace Quazal {
// forward decl cause i can't find the bastard
class DebugString;

class Job : public RefCountedObject {
    Job(const DebugString&);
};
}
