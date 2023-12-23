#include "storagechangedmsg.hpp"
#include "contentinstalledmsg.hpp"
#include "symbol.hpp"

ContentInstalledMsg::ContentInstalledMsg(DataArray* da) : Message(da) {

}

Symbol ContentInstalledMsg::Type(){
    static Symbol t("content_installed");
    return t;
}

StorageChangedMsg::StorageChangedMsg(DataArray* da) : Message(da) {

}

Symbol StorageChangedMsg::Type(){
    static Symbol t("storage_changed");
    return t;
}