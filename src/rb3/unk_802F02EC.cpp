#include "storagechangedmsg.hpp"
#include "symbol.hpp"

StorageChangedMsg::StorageChangedMsg(DataArray* da) : Message(da) {

}

Symbol GetStorageChangedMsgSymbol(){
    static Symbol t("storage_changed");
    return t;
}