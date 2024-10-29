#include "meta_band/LicenseMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"

LicenseMgr::LicenseMgr(){
    
}

bool LicenseMgr::HasLicense(Symbol s) const {
    return mLicenses.find(s) != mLicenses.end();
}

void LicenseMgr::ContentStarted(){
    mLicenses.clear();
}

bool LicenseMgr::ContentDiscovered(Symbol){ return true; }
const char* LicenseMgr::ContentPattern(){ return "licenses.dta"; }
const char* LicenseMgr::ContentDir(){ return "licenses"; }
void LicenseMgr::ContentMounted(const char*, const char*){}

void LicenseMgr::ContentLoaded(Loader* loader, ContentLocT ct, Symbol s){
    DataLoader* d = dynamic_cast<DataLoader*>(loader);
    MILO_ASSERT(d, 0x87);
    DataArray* data = d->Data();
    if(data){
        AddLicenses(data, d, ct, s);
    }
}

bool LicenseMgr::LicenseCacheNeedsWrite() const { return false; }
bool LicenseMgr::WriteCachedMetadataToStream(BinStream&) const { return false; }
bool LicenseMgr::ReadCachedMetadataFromStream(BinStream&, int){ return false; }
void LicenseMgr::ClearCachedContent(){}

void LicenseMgr::AddLicenses(DataArray* data, DataLoader* loader, ContentLocT ct, Symbol s){
    std::vector<Symbol> new_licenses;
    for(int i = 0; i < data->Size(); i++){
        Symbol new_license = data->Sym(i);
        MILO_ASSERT(!new_license.Null(), 0xF9);
        MarkAvailable(new_license, s);
        new_licenses.push_back(new_license);
    }
}

void LicenseMgr::MarkAvailable(Symbol s, Symbol){
    mLicenses.insert(s);
}