#ifndef META_METAMUSICMANAGER_H
#define META_METAMUSICMANAGER_H
#include "obj/Object.h"
#include "meta/MetaMusicScene.h"
#include <map>

class MetaMusicManager : public Hmx::Object {
public:
    MetaMusicManager(DataArray*);
    virtual ~MetaMusicManager();
    virtual DataNode Handle(DataArray*, bool);

    void Init(DataArray*);
    void Cleanup();

    std::map<Symbol, MetaMusicScene*> m_mapScenes; // 0x1c
    std::map<Symbol, Symbol> m_mapScreenToScene; // 0x34
};

extern MetaMusicManager* TheMetaMusicManager;

#endif
