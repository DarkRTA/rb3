#include "utl/Magnu.h"
#include "os/Debug.h"
#include "obj/Data.h"
#include "os/File.h"
#include "os/System.h"
#include "utl/Locale.h"
#include "obj/DataFunc.h"

extern bool UsingHolmes(int);
extern DataArray* DataReadFile(const char*, bool);
extern Locale TheLocale;

static DataNode MagnuRefreshStrings(DataArray* arr){
    DataArray* yeet = 0;
    if(UsingHolmes(2)){
        if(SystemExec(MakeString("%s\\sysutl_r.exe -magnu_strings", FileSystemRoot())) == 0){
            yeet = DataReadFile("magnu.dta", true);
        }
        else MILO_WARN("Failure running sysutl");
    }
    else MILO_WARN("Must be using Holmes to retrieve Magnu strings");

    if(yeet){
        TheLocale.SetMagnuStrings(yeet);
        return DataNode(yeet->Size());
    }
    else return DataNode(0);
}

static DataNode AddToken(DataArray* arr){
    MILO_WARN("Magnu add token only supported on PC");
    return DataNode(1);
}

static DataNode EditToken(DataArray* arr){
    MILO_WARN("Magnu edit token only supported on PC");
    return DataNode(1);
}

void MagnuInit(){
    DataRegisterFunc("add_token", AddToken);
    DataRegisterFunc("edit_token", EditToken);
    DataRegisterFunc("magnu_refresh_strings", MagnuRefreshStrings);
}
