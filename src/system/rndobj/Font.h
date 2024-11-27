#pragma once
#include "obj/Object.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "os/System.h"
#include "rndobj/Bitmap.h"
#include "utl/BinStream.h"
#include "utl/MemMgr.h"
#include <string.h>
#include <map>  

class RndMat;
class KerningTable;

struct MatChar {
    float width;
    float height;
};

/**
 * @brief Implements fonts for use with RndText objects.
 *  Additionally, RndFont can dynamically update the font atlas, cell sizes, and similar.
 *  Original _objects description:
 *   "Font objects determine the appearance for Text objects."
 */

class RndFont : public Hmx::Object {
public:

    struct CharInfo {
        float unk0;
        float unk4;
        float charWidth;
        float unkc;
    };

    struct KernInfo {
        unsigned short unk0;
        unsigned short unk2;
        float unk4;
    };

    RndFont();
    virtual ~RndFont();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(Font);
    OBJ_SET_TYPE(Font);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Print();

    void GetTexCoords(unsigned short, Vector2&, Vector2&) const;
    void GetKerning(std::vector<KernInfo>&) const;
    void SetKerning(const std::vector<KernInfo>&);
    void SetBaseKerning(float);
    void SetCellSize(float, float);
    void SetBitmapSize(const Vector2&, unsigned int, unsigned int);
    RndTex* ValidTexture() const;
    void UpdateChars();
    void BleedTest();
    int NonTransparentColumn(RndBitmap&, int, int, int, int);
    float CharAdvance(unsigned short, unsigned short) const;
    float CharAdvance(unsigned short) const;
    float Kerning(unsigned short, unsigned short) const;
    float CharWidth(unsigned short) const;
    bool CharDefined(unsigned short) const;
    void SetCharInfo(RndFont::CharInfo*, RndBitmap&, const Vector2&);
    String GetASCIIChars();
    void SetASCIIChars(String);

    RndMat* GetMat() const { return mMat; }
    void SetNextFont(RndFont* font){ unk78 = font; }
    RndFont* NextFont() const { return unk78; }
    bool IsMonospace() const { return mMonospace; }
    bool IsPacked() const { return mPacked; }
    float CellDiff() const { return mCellSize.y / mCellSize.x; }
    bool HasChar(unsigned short c) const {
        return mCharInfoMap.count(c) != 0;
    }

    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(RndFont)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFont)
    }
    DECLARE_REVS

    ObjPtr<RndMat> mMat; // 0x1c
    ObjOwnerPtr<RndFont> mTextureOwner; // 0x28
    std::map<unsigned short, CharInfo> mCharInfoMap; // 0x34
    KerningTable* mKerningTable; // 0x4c
    float mBaseKerning; // 0x50
    Vector2 mCellSize; // 0x54 - cell width, cell height
    float mDeprecatedSize; // 0x5c
    std::vector<unsigned short> mChars; // 0x60
    bool mMonospace; // 0x68
    Vector2 unk6c; // 0x6c
    bool mPacked; // 0x74
    ObjPtr<RndFont> unk78; // 0x78
};

class KerningTable {
public:
    struct Entry {
        Entry* next; // 0x0
        int key; // 0x4
        float kerning; // 0x8
    };

    KerningTable() : mNumEntries(0), mEntries(0) {
        memset(mTable, 0, 0x80);
    }

    ~KerningTable(){
        delete mEntries;
    }

    void GetKerning(std::vector<RndFont::KernInfo>& info) const {
        info.resize(mNumEntries);
        for(int i = 0; i < mNumEntries; i++){
            unsigned short& info0 = info[i].unk0;
            info0 = mEntries[i].key;
            unsigned short& info2 = info[i].unk2;
            info2 = (unsigned int)(mEntries[i].key) >> 16;
            float& info4 = info[i].unk4;
            info4 = mEntries[i].kerning;
        }
    }

    void SetKerning(const std::vector<RndFont::KernInfo>& info, RndFont* font){
        int validcount = 0;
        for(int i = 0; i < info.size(); i++){
            if(Valid(info[i], font)){
                validcount++;
            }
        }
        if(validcount != mNumEntries){
            mNumEntries = validcount;
            delete [] mEntries;
            mEntries = new Entry[mNumEntries];
        }
        memset(mTable, 0, 0x80);
        for(int i = 0; i < info.size(); i++){
            const RndFont::KernInfo& curInfo = info[i];
            if(Valid(curInfo, font)){
                Entry& curEntry = mEntries[i];
                curEntry.key = Key(curInfo.unk0, curInfo.unk2);
                curEntry.kerning = curInfo.unk4;
                int index = TableIndex(curInfo.unk0, curInfo.unk2);
                curEntry.next = mTable[index];
                mTable[index] = &curEntry;
            }
        }
    }

    bool Valid(const RndFont::KernInfo& info, RndFont* font){
        return !font || (font->CharDefined(info.unk0) && font->CharDefined(info.unk2));
    }

    int Key(unsigned short us0, unsigned short us2){
        return (us0 & 0xFFFF) | ((us2 << 0x10) & 0xFFFF0000);
    }

    int TableIndex(unsigned short us0, unsigned short us2){
        return (us0 ^ us2) & 0x1F;
    }

    int Size() const { return mNumEntries * 0xC + 0x88; }
    
    void Load(BinStream& bs, RndFont* font){
        if(RndFont::gRev < 7){
            std::vector<RndFont::KernInfo> kernInfos;
            bs >> kernInfos;
            SetKerning(kernInfos, font);
        }
        else {
            int size;
            bs >> size;
            if(size != mNumEntries){
                mNumEntries = size;
                delete [] mEntries;
                mEntries = new Entry[mNumEntries];
            }
            memset(mTable, 0, 0x80);
            for(int i = 0; i < mNumEntries; i++){
                Entry& curEntry = mEntries[i];
                bs >> curEntry.key;
                bs >> curEntry.kerning;
                unsigned short us4, us3;
                if(RndFont::gRev < 0x11){
                    us4 = curEntry.key & 0xFF;
                    us3 = curEntry.key >> 8 & 0xFF;
                    curEntry.key = Key(us4, us3);
                }
                else {
                    us4 = curEntry.key;
                    us3 = curEntry.key >> 16;
                }
                int idx = TableIndex(us4, us3);
                curEntry.next = mTable[idx];
                mTable[idx] = &curEntry;
            }
        }
    }

    int mNumEntries; // 0x0
    Entry* mEntries; // 0x4
    Entry* mTable[32]; // 0x8
};

class BitmapLocker {
public:
    BitmapLocker(RndFont* f) : mTexture(0), mPbm(0) {
        mTexture = f->ValidTexture();
        if(mTexture){
            const char* filestr = mTexture->mFilepath.c_str();
            int fplen = strlen(filestr);
#ifdef MILO_DEBUG
            if(UsingCD() || fplen < 4 || stricmp(filestr + fplen - 4, ".bmp") != 0){
#endif
                mTexture->LockBitmap(mBm, 3);
                if(mBm.Pixels()){
                    mPbm = &mBm;
                }
#ifdef MILO_DEBUG
            }
            else {
                mBm.LoadBmp(filestr, false, false);
                if(mBm.Pixels()){
                    mPbm = &mBm;
                }
                mTexture = nullptr;
            }
#endif
        }
    }

    ~BitmapLocker(){
        if(mTexture) mTexture->UnlockBitmap();
    }

    RndBitmap* PtrToBitmap() const { return mPbm; }

    RndTex* mTexture; // 0x0
    RndBitmap* mPbm; // 0x4
    RndBitmap mBm; // 0x8
};

BinStream& operator>>(BinStream&, MatChar&);
BinStream& operator>>(BinStream&, RndFont::KernInfo&);
