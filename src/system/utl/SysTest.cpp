#include "utl/SysTest.h"
#include <string.h>
#include "os/Debug.h"
#include "utl/MakeString.h"

void LogColumnInfo(TextStream* ts, DataArray* da, bool b){
    const char* sep = b ? ";" : ",";
    *ts << "Category" << sep << "CategoryName" << sep << "Column" << sep << "Budget" << sep << "BudgetType" << sep << "AlwaysShow" << sep << "Tooltip\n";
    for(int i = 1; i < da->Size(); i++){
        DataArray* arr = da->Array(i);
        const char* str = arr->Str(5);
        if(strchr(str, ',') != 0) FAIL("Tooltip \"%s\" may not contain commas", str);
        *ts << "column_info" << sep << arr->Str(0) << sep << arr->Str(1) << sep << MakeString<float>("%.3f", arr->Float(2)) << sep << arr->Int(3) << sep << arr->Int(4) << sep << str << "\n";
    }
    *ts << "\n";
}

const char* UnusedSystemTestStar = "*";
