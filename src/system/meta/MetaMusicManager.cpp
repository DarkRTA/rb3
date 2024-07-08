#include "meta/MetaMusicManager.h"
#include "obj/Dir.h"

MetaMusicManager* TheMetaMusicManager;

MetaMusicManager::MetaMusicManager(DataArray* da){
    MILO_ASSERT(!TheMetaMusicManager, 0x13);
    TheMetaMusicManager = this;
    SetName("metamusic_mgr", ObjectDir::Main());
    Init(da);
}

MetaMusicManager::~MetaMusicManager(){
    TheMetaMusicManager = 0;
    Cleanup();
}

void MetaMusicManager::Cleanup(){
    for(std::map<Symbol, MetaMusicScene*>::iterator it = m_mapScenes.begin(); it != m_mapScenes.end(); it++){
        delete it->second;
        it->second = 0;
    }
    m_mapScenes.clear();
    m_mapScreenToScene.clear();
}

void MetaMusicManager::Init(DataArray* da){
    ConfigureMetaMusicSceneData(da->FindArray("scenes", true));
}

// fn_80511280
void MetaMusicManager::ConfigureMetaMusicSceneData(DataArray* da){
    MILO_ASSERT(m_mapScenes.empty(), 0x38);
    for(int i = 1; i < da->Size(); i++){
        DataArray* pSceneArray = da->Array(i);
        MILO_ASSERT(pSceneArray, 0x3E);
        MetaMusicScene* pScene = new MetaMusicScene(pSceneArray);
        MILO_ASSERT(pScene, 0x42);
        Symbol scene_name = pScene->GetName(); 
        if(SceneExists(scene_name)){
            MILO_WARN("%s scene already exists, skipping", scene_name.Str());
            delete pScene;
        }
        else {
            m_mapScenes[scene_name] = pScene;
            const std::list<Symbol>& screenlist = pScene->GetScreenList();
            for(std::list<Symbol>::const_iterator it = screenlist.begin(); it != screenlist.end(); it++){
                Symbol theSymbol = *it;
                if(SceneForScreenExists(theSymbol)){
                    MILO_WARN("%s screen already referenced in a scene, skipping", theSymbol.Str());
                }
                else {
                    m_mapScreenToScene[theSymbol] = scene_name;
                }
            }
        }
    }
}

Symbol MetaMusicManager::GetSceneForScreen(Symbol s) const {
    std::map<Symbol, Symbol>::const_iterator it = m_mapScreenToScene.find(s);
    if(it != m_mapScreenToScene.end()) return it->second;
    else return gNullStr;
}

MetaMusicScene* MetaMusicManager::GetScene(Symbol s) const {
    std::map<Symbol, MetaMusicScene*>::const_iterator it = m_mapScenes.find(s);
    if(it != m_mapScenes.end()) return it->second;
    else return 0;
}

BEGIN_HANDLERS(MetaMusicManager)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8B)
END_HANDLERS