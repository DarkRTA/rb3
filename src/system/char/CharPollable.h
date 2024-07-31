#ifndef CHAR_CHARPOLLABLE_H
#define CHAR_CHARPOLLABLE_H
#include "rndobj/Poll.h"
#include <list>
#include <map>

class CharPollable : public RndPollable {
public:
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&) = 0;
    virtual ~CharPollable(){}
};

class CharPollableSorter {
public:
    class Dep {
    public:
        Hmx::Object* obj; // 0x0
        std::list<Hmx::Object*> changedBy; // 0x4 - is the list type different?
        RndPollable* poll; // 0xc
        int searchID; // 0x10
    };

    CharPollableSorter(){}

    void Sort(std::vector<RndPollable*>&);
    bool ChangedBy(Dep*, Dep*);
    bool ChangedByRecurse(Dep*);
    void AddDeps(Dep*, const std::list<Hmx::Object*>&, std::list<Dep*>&, bool);

    std::map<Hmx::Object*, Dep> mDeps;
    Dep* mTarget;
};

#endif
