#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"

extern void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

// fn_80301540
extern DataNode OnJoypadReset(DataArray*);
// fn_80301000
extern DataNode OnJoypadVibrate(DataArray*);
// fn_80300F98
extern DataNode OnJoypadSetVibrate(DataArray*);
// fn_80301044
extern DataNode OnJoypadControllerTypePadnum(DataArray*);
// fn_8030108C
extern DataNode OnJoypadIsConnectedPadnum(DataArray*);
// fn_803010D0
extern DataNode OnJoypadIsButtonDown(DataArray*);
// fn_8030114C
extern DataNode OnJoypadIsCalbertGuitar(DataArray*);

extern "C" void fn_80301C4C();
// fn_80301C4C
void fn_80301C4C(){
    DataRegisterFunc("joypad_reset", OnJoypadReset);
    DataRegisterFunc("joypad_vibrate", OnJoypadVibrate);
    DataRegisterFunc("joypad_set_vibrate", OnJoypadSetVibrate);
    DataRegisterFunc("joypad_controller_type_padnum", OnJoypadControllerTypePadnum);
    DataRegisterFunc("joypad_is_connected_padnum", OnJoypadIsConnectedPadnum);
    DataRegisterFunc("joypad_is_button_down", OnJoypadIsButtonDown);
    DataRegisterFunc("joypad_is_calbert_guitar", OnJoypadIsCalbertGuitar);
}