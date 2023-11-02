#include "data.hpp"
#include "symbol.hpp"
#include "keyboardkeyreleasedmsg.hpp"
#include "keyboardmodmsg.hpp"
#include "keyboardexpressionpedalmsg.hpp"
#include "keyboardconnectedaccessoriesmsg.hpp"
#include "keyboardsustainmsg.hpp"
#include "keyboardstompboxmsg.hpp"
#include "keysaccelerometermsg.hpp"
#include "keyboardlowhandplacementmsg.hpp"
#include "keyboardhighhandplacementmsg.hpp"

// fn_80315324
Symbol GetKeyboardKeyReleasedSymbol(){
    static Symbol lbl_808FC8B4("keyboard_key_released");
    return lbl_808FC8B4;
}

// fn_80315298
KeyboardKeyReleasedMsg::KeyboardKeyReleasedMsg(int i1, int i2) :
    Message(GetKeyboardKeyReleasedSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_803153FC
Symbol GetKeyboardModSymbol(){
    static Symbol lbl_808FC8B8("keyboard_mod");
    return lbl_808FC8B8;
}

// fn_80315370
KeyboardModMsg::KeyboardModMsg(int i1, int i2) :
    Message(GetKeyboardModSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_803154D4
Symbol GetKeyboardExpressionPedalSymbol(){
    static Symbol lbl_808FC8BC("keyboard_expression_pedal");
    return lbl_808FC8BC;
}

// fn_80315448
KeyboardExpressionPedalMsg::KeyboardExpressionPedalMsg(int i1, int i2) :
    Message(GetKeyboardExpressionPedalSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_803155AC
Symbol GetKeyboardConnectedAccessoriesSymbol(){
    static Symbol lbl_808FC8C0("keyboard_connected_accessories");
    return lbl_808FC8C0;
}

// fn_80315520
KeyboardConnectedAccessoriesMsg::KeyboardConnectedAccessoriesMsg(int i1, int i2) :
    Message(GetKeyboardConnectedAccessoriesSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_80315684
Symbol GetKeyboardSustainSymbol(){
    static Symbol lbl_808FC8C4("keyboard_sustain");
    return lbl_808FC8C4;
}

// fn_803155F8
KeyboardSustainMsg::KeyboardSustainMsg(int i1, int i2) :
    Message(GetKeyboardSustainSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_8031575C
Symbol GetKeyboardStompBoxSymbol(){
    static Symbol lbl_808FC8C8("keyboard_stomp_box");
    return lbl_808FC8C8;
}

// fn_803156D0
KeyboardStompBoxMsg::KeyboardStompBoxMsg(int i1, int i2) :
    Message(GetKeyboardStompBoxSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_80315874
Symbol GetKeysAccelerometerSymbol(){
    static Symbol lbl_808FC8CC("keys_accelerometer");
    return lbl_808FC8CC;
}

// fn_803157A8
KeysAccelerometerMsg::KeysAccelerometerMsg(int i1, int i2, int i3, int i4) :
    Message(GetKeysAccelerometerSymbol(), DataNode(i1), DataNode(i2), DataNode(i3), DataNode(i4)) { }

// fn_8031594C
Symbol GetKeyboardLowHandPlacementSymbol(){
    static Symbol lbl_808FC8D0("keyboard_low_hand_placement");
    return lbl_808FC8D0;
}

// fn_803158C0
KeyboardLowHandPlacementMsg::KeyboardLowHandPlacementMsg(int i1, int i2) :
    Message(GetKeyboardLowHandPlacementSymbol(), DataNode(i1), DataNode(i2)) { }

// fn_80315A24
Symbol GetKeyboardHighHandPlacementSymbol(){
    static Symbol lbl_808FC8D4("keyboard_high_hand_placement");
    return lbl_808FC8D4;
}

// fn_80315998
KeyboardHighHandPlacementMsg::KeyboardHighHandPlacementMsg(int i1, int i2) :
    Message(GetKeyboardHighHandPlacementSymbol(), DataNode(i1), DataNode(i2)) { }