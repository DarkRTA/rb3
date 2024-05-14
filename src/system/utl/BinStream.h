#ifndef UTL_BINSTREAM_H
#define UTL_BINSTREAM_H
#include "math/Rand2.h"
#include "types.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include <vector>

#define BS_WRITE_TYPE(var) \
    BinStream& operator<<(var x){ \
        WriteEndian(&x, sizeof(var)); \
        return *this; \
    }

#define BS_READ_TYPE(var) \
    BinStream& operator>>(var& x){ \
        ReadEndian(&x, sizeof(var)); \
        return *this; \
    }

enum EofType {
    NotEof = 0,
    RealEof = 1,
    TempEof = 2
};

class BinStream {
public:
    /** The three seek types for BinStream::Seek
     *
     * The three seek types used by BinStream::Seek. Presumably,
     * they are "start from beginning", "start from current
     * position", and "start from end".
     *
     * @see Seek()
     */
    enum SeekType {
        kSeekBegin = 0,
        kSeekCur = 1,
        kSeekEnd = 2,
    };

    BinStream(bool);
    virtual ~BinStream();
    virtual void Flush() = 0;
    virtual int Tell() = 0;
    virtual EofType Eof() = 0;
    virtual bool Fail() = 0;
    virtual const char* Name() const;
    virtual bool Cached() const { return false; }
    virtual int GetPlatform() const { return 0; }
    virtual void ReadImpl(void*, int) = 0;
    virtual void WriteImpl(const void*, int) = 0;
    virtual void SeekImpl(int, SeekType) = 0;

    /** Endianness flags, denotes whether to swap from native. */
    bool mLittleEndian;
    /** PRNG source, used for encryption */
    Rand2 *mCrypto;

    BinStream &operator<<(const char *);
    BinStream &operator<<(const Symbol &);
    BinStream &operator<<(const class String &);

    /** Reads a `len` length string to `out`.
     * Reads a standard C string of length `len` into `out` from
     * the open file.
     *
     * @param [out] out The pointer to read the string into.
     * @param [in] len The length of text to read.
     */
    void ReadString(char * out, int len);

    BinStream &operator>>(Symbol &);
    BinStream &operator>>(class String &);

    /** Enables read encryption for e.g. archives.
     * Enables read encryption, used for things such as archives.
     */
    void EnableReadEncryption();

    void EnableWriteEncryption();

    void DisableEncryption();

    /** Reads `len` bytes of data into `out`.
     * Reads a length of data specified by `len` from the open file
     * into `out`, using the native endianness (PPC == BE).
     *
     * @param [out] out The pointer to read data into.
     * @param [in] len The length of data to read.
     */
    void Read(void * out, int len);

    void Write(const void *, int);

    /** Seeks to `offset` using `mode`. */
    void Seek(int offset, SeekType mode);

    /** Reads `len` bytes of data into `out`, reversed if mLittleEndian is true.
     * Reads a length of data specified by `len` from the open file
     * into `out`, using the endianness specified by mLittleEndian.
     * (mLE == LE, therefore !mLE == BE)
     *
     * @param [out] out The pointer to read data into.
     * @param [in] len The length of data to read.
     */
    void ReadEndian(void * out, int len);

    void WriteEndian(const void *, int);

    bool LittleEndian() const { return mLittleEndian; }

    BS_WRITE_TYPE(int);
    BS_WRITE_TYPE(float);
    BS_WRITE_TYPE(unsigned int);
    BS_WRITE_TYPE(unsigned short);
    BS_WRITE_TYPE(short);

    BinStream& operator<<(unsigned char uc){
        Write(&uc, 1);
        return *this;
    }

    BinStream& operator<<(bool b){
        unsigned char uc = (b) ? 1 : 0;
        Write(&uc, 1);
        return *this;
    }

    BS_READ_TYPE(int);
    BS_READ_TYPE(float);
    BS_READ_TYPE(unsigned int);
    BS_READ_TYPE(short);
    BS_READ_TYPE(u16);
    BS_READ_TYPE(u32);
    BS_READ_TYPE(u64);
    BS_READ_TYPE(s32);
    BS_READ_TYPE(s64);

    BinStream& operator>>(unsigned char& out) {
        Read(&out, 1);
        return *this;
    }

    BinStream& operator>>(bool& b){
        unsigned char uc;
        *this >> uc;
        b = (uc != 0);
        return *this;
    }

};

template<class T1, class T2> BinStream& operator<<(BinStream& bs, const std::vector<T1, T2>& vec){
    bs << (int)vec.size();
    for(std::vector<T1, T2>::const_iterator it = vec.begin(); it != vec.end(); it++){
        bs << *it;
    }
    return bs;
}

template<class T1, class T2> BinStream& operator>>(BinStream& bs, std::vector<T1, T2>& vec){
    unsigned int length;
    bs >> length;
    vec.resize(length);

    for(std::vector<T1, T2>::iterator it = vec.begin(); it != vec.end(); it++){
        bs >> *it;
    }

    return bs;
}

#endif
