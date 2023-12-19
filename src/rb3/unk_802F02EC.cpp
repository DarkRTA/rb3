#include "storagechangedmsg.hpp"
#include "symbol.hpp"

StorageChangedMsg::StorageChangedMsg(DataArray* da) : Message(da) {

}

Symbol StorageChangedMsg::Type(){
    static Symbol t("storage_changed");
    return t;
}