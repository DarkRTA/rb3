#ifndef CHAR_CHARPOLLABLE_H
#define CHAR_CHARPOLLABLE_H
#include "rndobj/Poll.h"
#include <list>

class CharPollable : public RndPollable {
public:
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&) = 0;
    virtual ~CharPollable(){}
};

#endif
