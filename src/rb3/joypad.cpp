#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"

extern void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

namespace {

// fn_80301540
DataNode DataJoypadReset(DataArray* da){

}

// fn_80301000
DataNode OnJoypadVibrate(DataArray*){

}

// fn_80300F98
DataNode OnJoypadSetVibrate(DataArray*){

}

// fn_80301044
DataNode OnJoypadControllerTypePadnum(DataArray*){

}

// fn_8030108C
DataNode OnJoypadIsConnectedPadnum(DataArray*){

}

// fn_803010D0
DataNode OnJoypadIsButtonDown(DataArray*){

}

// fn_8030114C
DataNode OnJoypadIsCalbertGuitar(DataArray*){

}

}

extern "C" void JoypadInitCommon();

// fn_80301C4C
void JoypadInitCommon(){
    DataRegisterFunc("joypad_reset", DataJoypadReset);
    DataRegisterFunc("joypad_vibrate", OnJoypadVibrate);
    DataRegisterFunc("joypad_set_vibrate", OnJoypadSetVibrate);
    DataRegisterFunc("joypad_controller_type_padnum", OnJoypadControllerTypePadnum);
    DataRegisterFunc("joypad_is_connected_padnum", OnJoypadIsConnectedPadnum);
    DataRegisterFunc("joypad_is_button_down", OnJoypadIsButtonDown);
    DataRegisterFunc("joypad_is_calbert_guitar", OnJoypadIsCalbertGuitar);
}