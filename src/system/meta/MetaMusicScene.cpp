#include "meta/MetaMusicScene.h"
#include "os/Debug.h"
#include "utl/Symbols.h"

MetaMusicScene::MetaMusicScene(DataArray* da) : m_symName(""), mMix(0) {
    Configure(da);
}

MetaMusicScene::~MetaMusicScene(){
    
}

void MetaMusicScene::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x1A);
    m_symName = i_pConfig->Sym(0);
    DataArray* screens_found = i_pConfig->FindArray(screens, false);
    if(screens_found){
        for(int i = 1; i < screens_found->Size(); i++){
            m_lScreens.push_back(screens_found->Sym(i));
        }
    }
    mMix = i_pConfig->FindArray(mix, false);
}

Symbol MetaMusicScene::GetName() const {
    return m_symName;
}

const std::list<Symbol>& MetaMusicScene::GetScreenList() const {
    return m_lScreens;
}
