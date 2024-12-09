#include "ui/LocalePanel.h"
#include "ui/UI.h"
#include "ui/UIList.h"
#include "ui/UIListLabel.h"
#include "ui/UILabel.h"
#include "ui/UIListWidget.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"

namespace {
    struct LabelSort {
        bool operator()(const UILabel* u1, const UILabel* u2) const {
            return stricmp(u1->TextToken().Str(), u2->TextToken().Str()) < 0;
        }
    };
}

void LocalePanel::Enter(){
    mEntries.clear();
    UIScreen* screen = Screen();
    for(std::vector<PanelRef>::iterator it = screen->mPanelList.begin(); it != screen->mPanelList.end(); ++it){
        AddDirEntries(it->mPanel->mDir, it->mPanel->Name());
    }
    UIPanel::Enter();
}

void LocalePanel::Text(int i, int j, UIListLabel* listlabel, UILabel* label) const {
    Entry* entry = (Entry*)&mEntries[j];
    if(listlabel->Matches("heading")){
        label->SetEditText(entry->mHeading.c_str());
    }
    else if(listlabel->Matches("label")){
        label->SetEditText(entry->mLabel.c_str());
    }
    else if(listlabel->Matches("token")){
        label->SetEditText(entry->mToken.Str());
    }
    else if(listlabel->Matches("string")){
        label->SetEditText(entry->mString.c_str());
    }
}

int LocalePanel::NumData() const { return mEntries.size(); }

bool LocalePanel::IsActive(int i) const { return !mEntries[i].mLabel.empty(); }

float LocalePanel::GapSize(int, int i, int, int) const {
    if(IsActive(i)) return 30.0f;
    else return 0;
}

UIScreen* LocalePanel::Screen(){
    return TheUI->ScreenAtDepth(TheUI->PushDepth() - 1);
}

void LocalePanel::AddDirEntries(ObjectDir* dir, const char* cc){
    std::vector<UILabel*> labels;
    for(ObjDirItr<UILabel> it(dir, true); it != nullptr; ++it){
        if(it->Showing()) labels.push_back(it);
    }
    std::sort(labels.begin(), labels.end(), LabelSort());
    if(!labels.empty()){
        AddHeading(MakeString("%s: %s", cc ? cc : "proxy", PathName(this)));
    }
    for(std::vector<UILabel*>::iterator it = labels.begin(); it != labels.end(); ++it){
        UILabel* cur = *it;
        Entry entry;
        entry.mLabel = cur->Name();
        entry.mToken = TokenForLabel(cur);
        entry.mString = cur->TextObj()->mText.c_str();
        mEntries.push_back(entry);
    }
    for(ObjDirItr<UIList> it(dir, true); it != nullptr; ++it){
        if(it->Showing()){
            AddHeading(MakeString("%s: %s", it->ClassName(), it->Name()));
            const std::vector<UIListWidget*>& widgets = it->GetWidgets();
            for(int i = 0; i < it->NumDisplay(); i++){
                for(std::vector<UIListWidget*>::const_iterator wIt = widgets.begin(); wIt != widgets.end(); ++wIt){
                    UIListLabel* listLabel = dynamic_cast<UIListLabel*>(*wIt);
                    if(listLabel){
                        UILabel* elementLabel = listLabel->ElementLabel(i);
                        if(elementLabel){
                            if(elementLabel->TextObj()->mText.length() != 0){
                                Entry entry;
                                entry.mLabel = MakeString("%i:%s", i, listLabel->MatchName());
                                entry.mToken = TokenForLabel(elementLabel);
                                entry.mString = elementLabel->TextObj()->mText.c_str();
                                mEntries.push_back(entry);
                            }
                        }
                    }
                }
            }
        }
    }
    for(ObjDirItr<PanelDir> it(dir, true); it != nullptr; ++it){
        if(it != dir){
            AddDirEntries(it, 0);
        }
    }
}