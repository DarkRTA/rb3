#ifndef META_HAQMANAGER_H
#define META_HAQMANAGER_H
#include "obj/Object.h"
#include "utl/Str.h"
#include "os/Joypad.h"

class UIComponent;
class UIList;
class UISlider;

enum HAQType {
    kHAQType_Screen,
    kHAQType_Focus,
    kHAQType_Button,
    kHAQType_Slider,
    kHAQType_List,
    kHAQType_Song,
    kHAQType_Checkbox
};

class HAQManager : public Hmx::Object {
public:
    HAQManager();
    virtual ~HAQManager();
    virtual DataNode Handle(DataArray*, bool);

    String GetLabelForType(HAQType) const;
    String GetTextForType(HAQType) const;
    String GetScreenText() const;
    String GetFocusText() const;
    String GetButtonText() const;
    UIComponent* GetUIFocusComponent() const;
    void PrintList(UIList*);
    void PrintSlider(UISlider*);
    void PrintComponentInfo(UIComponent*);
    String GetPressedStringForButton(int, JoypadButton, String) const;
    String GetButtonStatePressedString(int) const;
    bool Enabled() const { return m_bEnabled; }
    void ToggleEnabled();
    void DisplayAll();

    static void Init();
    static void PrintSongInfo(Symbol, float);
    static void Print(HAQType, Hmx::Object*, int);
    static void Print(HAQType);
    static void RawPrint(const char*, const char*);
    static void HandleComponentScroll(UIComponent*);

    bool m_bEnabled; // 0x1c
};

extern HAQManager* TheHAQMgr;

#endif
