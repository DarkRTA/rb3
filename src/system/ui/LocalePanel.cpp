#include "ui/LocalePanel.h"
#include "ui/UIListLabel.h"
#include "ui/UILabel.h"

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