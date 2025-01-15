#pragma once
#include "rndobj/Poll.h"
#include <list>
#include <map>

/** "Workhorse unit of the Character system, most Character things inherit from this." */
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
        std::list<Dep*> changedBy; // 0x4
        RndPollable* poll; // 0xc
        int searchID; // 0x10
    };

    struct AlphaSort {
        bool operator()(Dep* d1, Dep* d2) const { return strcmp(d1->obj->Name(), d2->obj->Name()) < 0; }
    };

    CharPollableSorter(){}

    void Sort(std::vector<RndPollable*>&);
    bool ChangedBy(Dep*, Dep*);
    bool ChangedByRecurse(Dep*);
    void AddDeps(Dep*, const std::list<Hmx::Object*>&, std::list<Dep*>&, bool);

    static int sSearchID;

    std::map<Hmx::Object*, Dep> mDeps;
    Dep* mTarget;
};
