#include "meta/HAQManager.h"
#include "os/Debug.h"
#include "obj/Dir.h"
#include "ui/UI.h"
#include "ui/UIScreen.h"
#include "ui/UIComponent.h"
#include "ui/UIList.h"
#include "ui/UISlider.h"
#include "utl/Symbols.h"

HAQManager* TheHAQMgr;

HAQManager::HAQManager() : m_bEnabled(0) {
    MILO_ASSERT(!TheHAQMgr, 0x1A);
    TheHAQMgr = this;
    SetName("haq_mgr", ObjectDir::Main());
}

HAQManager::~HAQManager(){

}

void HAQManager::Init(){

}

String HAQManager::GetLabelForType(HAQType type) const {
    String ret("");
    switch(type){
        case kHAQType_Screen: ret = "Screen"; break;
        case kHAQType_Focus: ret = "Focus"; break;
        case kHAQType_Button: ret = "Button"; break;
        case kHAQType_Slider: ret = "Slider"; break;
        case kHAQType_List: ret = "List"; break;
        case kHAQType_Song: ret = "Song"; break;
        default: MILO_ASSERT(false, 0x50); break;
    }
    return ret;
}

String HAQManager::GetScreenText() const {
    const char* cc;
    UIScreen* screen = TheUI->CurrentScreen();
    if(screen) cc = screen->Name();
    else cc = "<NONE>";
    return String(cc);
}

String HAQManager::GetFocusText() const {
    String str("<NONE>");
    UIComponent* comp = GetUIFocusComponent();
    if(comp) str = comp->Name();
    return str;
}

void HAQManager::PrintComponentInfo(UIComponent* comp){
    UIList* list = dynamic_cast<UIList*>(comp);
    if(list) PrintList(list);
    UISlider* slider = dynamic_cast<UISlider*>(comp);
    if(slider) PrintSlider(slider);
}

String HAQManager::GetPressedStringForButton(int padnum, JoypadButton btn, String str) const {
    JoypadData* pData = JoypadGetPadData(padnum);
    MILO_ASSERT(pData, 0x82);
    if(pData->IsButtonInMask(btn)){
        return String(MakeString("%s ", str));
    }
    else return String("");
}

String HAQManager::GetButtonStatePressedString(int pad) const {
    String ret("");
    ret += GetPressedStringForButton(pad, kPad_Xbox_A, "A");
    ret += GetPressedStringForButton(pad, kPad_Xbox_B, "B");
    ret += GetPressedStringForButton(pad, kPad_Xbox_X, "X");
    ret += GetPressedStringForButton(pad, kPad_Xbox_Y, "Y");
    ret += GetPressedStringForButton(pad, kPad_Xbox_LS, "J");
    ret += GetPressedStringForButton(pad, kPad_Xbox_RS, "C");
    ret += GetPressedStringForButton(pad, kPad_Xbox_LB, "LS");
    ret += GetPressedStringForButton(pad, kPad_Xbox_RB, "RS");
    ret += GetPressedStringForButton(pad, kPad_Start, "S");
    ret += GetPressedStringForButton(pad, kPad_Select, "Z");
    ret += GetPressedStringForButton(pad, kPad_DUp, "DU");
    ret += GetPressedStringForButton(pad, kPad_DDown, "DD");
    ret += GetPressedStringForButton(pad, kPad_DLeft, "DL");
    ret += GetPressedStringForButton(pad, kPad_DRight, "DR");
    ret += GetPressedStringForButton(pad, kPad_Xbox_LT, "LT");
    ret += GetPressedStringForButton(pad, kPad_Xbox_RT, "RT");
    ret += GetPressedStringForButton(pad, kPad_LStickUp, "JU");
    ret += GetPressedStringForButton(pad, kPad_LStickRight, "JR");
    ret += GetPressedStringForButton(pad, kPad_LStickDown, "JD");
    ret += GetPressedStringForButton(pad, kPad_LStickLeft, "JL");
    ret += GetPressedStringForButton(pad, kPad_RStickUp, "CU");
    ret += GetPressedStringForButton(pad, kPad_RStickRight, "CR");
    ret += GetPressedStringForButton(pad, kPad_RStickDown, "CD");
    ret += GetPressedStringForButton(pad, kPad_RStickLeft, "CL");
    return ret;
}

UIComponent* HAQManager::GetUIFocusComponent() const {
    UIComponent* ret = 0;
    UIScreen* screen = TheUI->CurrentScreen();
    if(screen){
        UIPanel* focus = screen->mFocusPanel;
        if(focus) ret = focus->FocusComponent();
    }
    return ret;
}

void HAQManager::PrintList(UIList* i_pList){
    MILO_ASSERT(i_pList, 0xC2);
    int pos = i_pList->SelectedPos();
    Print(kHAQType_List, i_pList, pos);
}

void HAQManager::PrintSlider(UISlider* slider){
    Print(kHAQType_Slider, slider, slider->Current());
}

void HAQManager::PrintSongInfo(Symbol s, float f){
    if(TheHAQMgr && TheHAQMgr->Enabled()){
        String text = String(MakeString("%s %f", s, f / 1000.0f));
        String label = TheHAQMgr->GetLabelForType(kHAQType_Song);
        RawPrint(label.c_str(), text.c_str());
    }
}

String HAQManager::GetButtonText() const {
    String ret("");
    for(int i = 0; i < 4; i++){
        ret += MakeString("%i %s | ", i, String(GetButtonStatePressedString(i)));
    }
    return ret;
}

String HAQManager::GetTextForType(HAQType ty) const {
    String ret("");
    switch(ty){
        case kHAQType_Screen:
            ret = GetScreenText();
            break;
        case kHAQType_Focus:
            ret = GetFocusText();
            break;
        case kHAQType_Button:
            ret = GetButtonText();
            break;
        default:
            MILO_ASSERT(false, 0xFD);
            break;
    }
    return ret;
}

void HAQManager::Print(HAQType ty, Hmx::Object* o, int i){
    if(TheHAQMgr && TheHAQMgr->Enabled()){
        String label = TheHAQMgr->GetLabelForType(ty);
        String text = String(MakeString("%s %i", o->Name(), i));
        RawPrint(label.c_str(), text.c_str());
    }
}

void HAQManager::Print(HAQType ty){
    if(TheHAQMgr && TheHAQMgr->Enabled()){
        String label = TheHAQMgr->GetLabelForType(ty);
        String text = TheHAQMgr->GetTextForType(ty);
        RawPrint(label.c_str(), text.c_str());
        if(ty == kHAQType_Focus){
            UIComponent* comp = TheHAQMgr->GetUIFocusComponent();
            if(comp) TheHAQMgr->PrintComponentInfo(comp);
        }
    }
}

void HAQManager::RawPrint(const char* c1, const char* c2){
    if(TheHAQMgr && TheHAQMgr->Enabled()){
        MILO_LOG("HAQ_%s: %s\n", c1, c2);
    }
}

void HAQManager::ToggleEnabled(){
    m_bEnabled = !m_bEnabled;
}

void HAQManager::DisplayAll(){
    if(!m_bEnabled) ToggleEnabled();
    Print(kHAQType_Screen);
    Print(kHAQType_Focus);
}

void HAQManager::HandleComponentScroll(UIComponent* comp){
    if(TheHAQMgr && TheHAQMgr->Enabled()){
        TheHAQMgr->PrintComponentInfo(comp);
    }
}

BEGIN_HANDLERS(HAQManager)
    HANDLE_ACTION(toggle_enabled, ToggleEnabled())
    HANDLE_EXPR(is_enabled, m_bEnabled)
    HANDLE_ACTION(display_all, DisplayAll())
    HANDLE_ACTION(raw_print, RawPrint(_msg->Str(2), _msg->Str(3)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x164)
END_HANDLERS