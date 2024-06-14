#include "ui/UIListProvider.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"

void UIListProvider::Text(int, int, UIListLabel* listlabel, UILabel* label) const {
    if(TheLoadMgr.EditMode()){
        label->SetEditText(listlabel->GetDefaultText());
    }
    else {
        label->SetTextToken(gNullStr);
    }
}

RndMat* UIListProvider::Mat(int, int, UIListMesh* mesh) const {
    return mesh->DefaultMat();
}

void UIListProvider::UpdateExtendedText(int, int, UILabel* label) const {
    if(!TheLoadMgr.EditMode()){
        MILO_WARN("Trying to update extended text without an override provider method. Label = %s", label->Name());
        label->SetTextToken(gNullStr);
    }
}

void UIListProvider::UpdateExtendedMesh(int, int, RndMesh* mesh) const {
    if(!TheLoadMgr.EditMode()){
        MILO_WARN("Trying to update extended mesh without an override provider method. Mesh = %s", mesh->Name());
        mesh->SetMat(0);
    }
}

void UIListProvider::UpdateExtendedCustom(int, int, Hmx::Object* obj) const {
    if(!TheLoadMgr.EditMode()){
        MILO_WARN("Trying to update extended custom object without an override provider method. object = %s", obj->Name());
    }
}