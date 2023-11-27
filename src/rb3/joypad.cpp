#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"

extern void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

extern void JoypadSetVibrate(int, bool);
extern int JoypadVibrate(int);
extern Symbol JoypadControllerTypePadNum(int);
extern int JoypadIsConnectedPadNum(int);

namespace {
    // fn_80301540
    DataNode DataJoypadReset(DataArray* da){

    }

    // fn_80301000
    DataNode OnJoypadVibrate(DataArray* da){
        return DataNode(JoypadVibrate(da->GetIntAtIndex(1)));
    }

    // fn_80300F98
    DataNode OnJoypadSetVibrate(DataArray* da){
        JoypadSetVibrate(da->GetIntAtIndex(1), (da->GetIntAtIndex(2) != 0));
        return DataNode(1);
    }

    // fn_80301044
    DataNode OnJoypadControllerTypePadNum(DataArray* da){
        return DataNode(JoypadControllerTypePadNum(da->GetIntAtIndex(1)));
    }

    // fn_8030108C
    DataNode OnJoypadIsConnectedPadNum(DataArray* da){
        return DataNode(JoypadIsConnectedPadNum(da->GetIntAtIndex(1)));
    }

    // fn_803010D0
    DataNode OnJoypadIsButtonDownPadNum(DataArray*){

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
    DataRegisterFunc("joypad_controller_type_padnum", OnJoypadControllerTypePadNum);
    DataRegisterFunc("joypad_is_connected_padnum", OnJoypadIsConnectedPadNum);
    DataRegisterFunc("joypad_is_button_down", OnJoypadIsButtonDownPadNum);
    DataRegisterFunc("joypad_is_calbert_guitar", OnJoypadIsCalbertGuitar);
}