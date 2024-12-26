#include "utl/Locale.h"
#include "obj/DataFile.h"
#include "obj/DataFunc.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/DataPointMgr.h"
#include "utl/Symbols.h"

Locale TheLocale;
int gDbgLocaleNumEntries;
int gDbgLocaleStringsSize;
bool Locale::sVerboseNotify;

DataNode DataSetLocaleVerboseNotify(DataArray* arr){
    SetLocaleVerboseNotify(arr->Int(1));
    return 0;
}

DataNode DataDbgPrintLocaleSize(DataArray*){
    MILO_LOG("Localization table: %d entries, %gK in strings. Total mem: %gK\n",
        gDbgLocaleNumEntries, (float)gDbgLocaleStringsSize * 0.0009765625f,
        (float)(gDbgLocaleStringsSize + gDbgLocaleNumEntries * 4) * 0.0009765625f);
    return 0;
}

Locale::~Locale(){
    if(mMagnuStrings){
        mMagnuStrings->Release();
        mMagnuStrings = 0;
    }
}

void Locale::Init(){
    MILO_ASSERT(!mStrTable, 0x5A);
    MILO_ASSERT(!mSymTable, 0x5B);
    MILO_ASSERT(!mSize, 0x5C);
    MILO_ASSERT(!mStringData, 0x5D);
    MILO_ASSERT(!mNumFilesLoaded, 0x5E);
    MILO_ASSERT(!mUploadedFlags, 0x60);

    int i13 = 0;
    int i10 = 0;
    int numChunks;
    LocaleChunkSort::OrderedLocaleChunk* chunks;
    Symbol s60;
    DataArray* cfg = SystemConfig("locale");
    {
        std::vector<DataArray*> arrVec(cfg->Size() - 1);
        mNumFilesLoaded = arrVec.size();
        for(int i = 1; i < cfg->Size(); i++){
            const char* path = FileMakePath(FileGetPath(cfg->File(), 0), cfg->Str(i), 0);
            arrVec[i - 1] = DataReadFile(path, true);
            if(arrVec[i - 1] == nullptr){
                MILO_FAIL("could not load language file %s", path);
            }
            i10 += arrVec[i - 1]->Size();
        }
        chunks = new LocaleChunkSort::OrderedLocaleChunk[i10];
        numChunks = 0;
        for(int j = cfg->Size() - 2; j >= 0; j--){
            DataArray* curArr = arrVec[j];
            for(int k = curArr->Size() - 1; k >= 0; k--, numChunks++){
                DataArray* chunkArr = curArr->Node(k).LiteralArray(curArr);
                int size = chunkArr->Size();
                if(size != 2){
                    MILO_FAIL("%s line %d should only have 2 entries, has %d, mismatched quotes?", chunkArr->File(), chunkArr->Line(), size);
                }
                chunks[numChunks].node1 = chunkArr->LiteralSym(0);
                chunks[numChunks].node2 = numChunks;
                chunks[numChunks].node3 = chunkArr->LiteralStr(1);
            }
            curArr->Release();
        }

        if(cfg->Size() > 1) LocaleChunkSort::Sort(chunks, numChunks);
        mSize = 0;
        for(int i = 0; i < numChunks; i++){
            Symbol curSym = chunks[i].node1.LiteralSym();
            if(curSym != s60){
                i13 += strlen(chunks[i].node3.LiteralStr());
                s60 = curSym;
                mSize++;
            }
        }
    }
    mSymTable = new Symbol[mSize];
    mStringData = new StringTable(i13);
    mStrTable = new const char*[mSize];
    int chunkIdx = 0;
    s60 = Symbol();
    for(int i = 0; i < numChunks; i++){
        Symbol curSym = chunks[i].node1.LiteralSym();
        if(curSym != s60){
            mSymTable[chunkIdx] = curSym;
            mStrTable[chunkIdx] = mStringData->Add(chunks[i].node3.LiteralStr());
            s60 = curSym;
            chunkIdx++;
        }
        else MILO_WARN("Locale symbol '%s' redefined", curSym.mStr);
    }
    delete [] chunks;
    if(cfg->Size() > 1){
        mFile = cfg->Str(1);
    }
    gDbgLocaleNumEntries = mSize;
    gDbgLocaleStringsSize = mStringData->UsedSize();
    DataRegisterFunc("dbg_print_locale_size", DataDbgPrintLocaleSize);
    DataRegisterFunc("set_locale_verbose_notify", DataSetLocaleVerboseNotify);
}

void Locale::Terminate(){
    delete [] mSymTable;
    mSymTable = 0;
    delete [] mStrTable;
    mStrTable = 0;
    delete [] mUploadedFlags;
    mUploadedFlags = 0;
    RELEASE(mStringData);
    mSize = 0;
    mFile = Symbol();
    mNumFilesLoaded = 0;
}

void Locale::SetMagnuStrings(DataArray* da){
    if(mMagnuStrings){
        mMagnuStrings->Release();
        mMagnuStrings = 0;
    }
    mMagnuStrings = da;
}

const char* Locale::Localize(Symbol s, bool b) const {
    if(s.Null()) return "";
    else if(!mSymTable){
        MILO_WARN("attempting to localize %s before Locale initialized!\n", s.mStr);
        return s.mStr;
    }
    else {
        MILO_ASSERT(mSymTable, 0x1F0);
        if(mMagnuStrings && SystemLanguage() == eng){
            DataArray* magnuArr = mMagnuStrings->FindArray(s, false);
            if(magnuArr){
                return magnuArr->Str(1);
            }
        }
        int iii;
        if(FindDataIndex(s, iii, b)){
            if(UsingCD() && !mUploadedFlags[iii]){
                SendDataPoint("debug/locale/token", "token", s, "success", true);
                mUploadedFlags[iii] = true;
            }
            return mStrTable[iii];
        }
        else if(UsingCD()){
            SendDataPoint("debug/locale/token", "token", s, "success", false);
        }
        return nullptr;
    }
}

bool Locale::FindDataIndex(Symbol s, int& idx, bool fail) const {
    if(fail){
        MILO_FAIL("Couldn't find '%s' in array (file %s)", s.mStr, mFile.mStr);
    }
    return false;
}

const char* Localize(Symbol token, bool* notify){
    const char* textStr = TheLocale.Localize(token, false);
    bool localized = textStr != 0;
    if(!localized){
        Locale::sIgnoreMissingText = textStr;
        if(Locale::sVerboseNotify != 0){
            MILO_WARN("\"%s\" needs localization", token);
        }
    }
    if(notify) *notify = localized;
    return textStr;
}
