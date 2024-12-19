#pragma once
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
    void ConfigureMetaMusicSceneData(DataArray*);
    Symbol GetSceneForScreen(Symbol) const;
    MetaMusicScene* GetScene(Symbol) const;

    bool SceneExists(Symbol s) const { return GetScene(s) != 0; }
    bool SceneForScreenExists(Symbol s) const { return GetSceneForScreen(s) != gNullStr; }

    std::map<Symbol, MetaMusicScene*> m_mapScenes; // 0x1c
    std::map<Symbol, Symbol> m_mapScreenToScene; // 0x34
};

extern MetaMusicManager* TheMetaMusicManager;
