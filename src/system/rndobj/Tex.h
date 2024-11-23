#pragma once
#include "obj/Object.h"
#include "rndobj/Bitmap.h"
#include "utl/BinStream.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"


/**
 * @brief A texture.
 * Original _objects description:
 * "Tex objects represent bitmaps used by materials. These
 * can be created automatically with 'import tex' on the file menu."
 */
class RndTex : public Hmx::Object {
public:
    enum Type {
        kRegular = 1,
        kRendered = 2,
        kMovie = 4,
        kBackBuffer = 8,
        kFrontBuffer = 0x18,
        kRenderedNoZ = 0x22,
        kShadowMap = 0x42,
        kDepthVolumeMap = 0xA2,
        kDensityMap = 0x122,
        kScratch = 0x200,
        kDeviceTexture = 0x1000
    };

    RndTex();
    virtual ~RndTex();
    OBJ_CLASSNAME(RndTex)
    OBJ_SET_TYPE(RndTex)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void Print();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SetMipMapK(float f){ mMipMapK = f; }
    virtual void LockBitmap(RndBitmap&, int);
    virtual void UnlockBitmap() {}
    virtual void MakeDrawTarget() {}
    virtual void FinishDrawTarget() {}
    virtual void Compress(bool) {}
    virtual bool TexelsLock(void*&) {return false;}
    virtual void TexelsUnlock() {}
    virtual int TexelsPitch() const { return 0; }
    virtual void Select(int) {}
    virtual void PresyncBitmap() ;
    virtual void SyncBitmap() ;

    /** Set this texture's bitmap using the supplied parameters.
     * @param [in] w The texture's width.
     * @param [in] h The texture's height.
     * @param [in] bpp The texture's bpp.
     * @param [in] ty The texture's type.
     * @param [in] useMips If true, generate a mipmap with this texture's bitmap.
     * @param [in] path The path to the texture.
     */
    void SetBitmap(int w, int h, int bpp, Type ty, bool useMips, const char* path);
    /** Set this texture's bitmap using the supplied parameters.
     * @param [in] bmap The bitmap to assign to this texture.
     * @param [in] path The path to the texture.
     * @param [in] b TODO: currently unknown.
     */
    void SetBitmap(const RndBitmap& bmap, const char* path, bool b);
    void SetBitmap(FileLoader*);
    void SetBitmap(const FilePath&);
    /** Unused. Presumably saves the bitmap of this texture to a supplied filename. */
    void SaveBitmap(const char*);
    /** Determine whether this texture's dimensions are both powers of 2. */
    void SetPowerOf2();

    /** Handler to set this texture's type to rendered.
     * Example usage: {$this set_rendered}
     */
    DataNode OnSetRendered(const DataArray*);
    /** Handler to set this texture's bitmap.
     * @param [in] arr The supplied DataArray.
     * Expected DataArray contents: 
     *     Node 2: A string containing the path to the texture.
     * Example usage: {$this set_bitmap texture.tex}
     * OR
     * Expected DataArray contents: 
     *     Node 2: The texture width.
     *     Node 3: The texture height.
     *     Node 4: The texture bpp.
     *     Node 5: The texture type.
     *     Node 6: Whether or not to set a mipmap.
     * Example usage: {$this set_bitmap 512 512 24 kRendered TRUE}
     */
    DataNode OnSetBitmap(const DataArray* arr);

    /** Validate the texture based on the supplied properties.
     * @param [in] width The texture's width.
     * @param [in] height The texture's height.
     * @param [in] bpp The texture's bpp.
     * @param [in] numMips The number of mips this texture has.
     * @param [in] ty The texture's type.
     * @param [in] file Param name is from RB2 DWARF, unknown what this is for.
     * @returns An error message if there were issues found.
     */
    static const char* CheckSize(int width, int height, int bpp, int numMips, Type ty, bool file);
    /** Get the appropriate texture bpp and order for this platform.
     * @param [in] path The path to the texture.
     * @param [out] bpp The bpp a texture on this platform should have.
     * @param [out] order The order a texture on this platform should have.
     * @param [in] hasAlpha If true, factor alpha into the resulting order.
     */
    static void PlatformBppOrder(const char* path, int& bpp, int& order, bool hasAlpha);

    int SizeKb() const { return ((mWidth * mHeight * mBpp) / 8 / 1024); }
    bool IsRenderTarget() const { return mType & kRendered; }
    int Width() const { return mWidth; }
    int Height() const { return mHeight; }
    Type GetType() const { return mType; }
    const FilePath& File() const { return mFilepath; }
    int NumMips() const { return mNumMips; }
    int Bpp() const { return mBpp; }

    DECLARE_REVS
    NEW_OVERLOAD
    NEW_OBJ(RndTex)
    DELETE_OVERLOAD;
    static void Init(){
        REGISTER_OBJ_FACTORY(RndTex)
    }

    /** The bitmap associated with this texture. */
    RndBitmap mBitmap; // 0x1c
    float mMipMapK; // 0x38
    /** The texture's type. */
    Type mType; // 0x3C
    /** The texture's width, in pixels. */
    int mWidth; // 0x40
    /** The texture's height, in pixels. */
    int mHeight; // 0x44
    /** The texture's bits per pixel. */
    int mBpp; // 0x48
    /** The texture's file. */
    FilePath mFilepath; // 0x4C
    /** The number of mips in this texture's mipmap. */
    int mNumMips; // 0x58
    /** Whether or not this texture's width and height are powers of 2. */
    bool mIsPowerOf2; // 0x5C
    /** Unused. Presumably, whether to use specialized computations for the PS3. */
    bool mOptimizeForPS3; // 0x5D
    FileLoader* mLoader; // 0x60
};

TextStream& operator<<(TextStream&, RndTex::Type);
