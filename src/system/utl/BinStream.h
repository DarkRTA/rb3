#pragma once
#include "math/Rand2.h"
#include "types.h"
#include "os/Platform.h"
#include "utl/Std.h"
#include "utl/Str.h"
#include "utl/Symbol.h"
#include <utility>
#include <vector>
#include <map>

#define BS_WRITE_OP(var)                                                                 \
    BinStream &operator<<(var x) {                                                       \
        WriteEndian(&x, sizeof(var));                                                    \
        return *this;                                                                    \
    }

#define BS_READ_OP(var)                                                                  \
    BinStream &operator>>(var &x) {                                                      \
        ReadEndian(&x, sizeof(var));                                                     \
        return *this;                                                                    \
    }

#define BS_READ_FUNC(var, name)                                                          \
    var Read##name() {                                                                   \
        var val;                                                                         \
        *this >> val;                                                                    \
        return val;                                                                      \
    }

enum EofType {
    NotEof = 0,
    RealEof = 1,
    TempEof = 2
};

/** A stream of raw bytes. Can be read from or written to. */
class BinStream {
public:
    /**
     * @brief The three seek types for BinStream::Seek.
     * @see Seek()
     */
    enum SeekType {
        kSeekBegin = 0,
        kSeekCur = 1,
        kSeekEnd = 2,
    };

    BinStream(bool littleEndian);
    virtual ~BinStream();
    /** Completely flush out this BinStream. */
    virtual void Flush() = 0;
    /** Get the current position of the BinStream. */
    virtual int Tell() = 0;
    /** Get the current End Of File type of the BinStream. */
    virtual EofType Eof() = 0;
    /** Get whether or not the BinStream has failed. */
    virtual bool Fail() = 0;
    /** Get this BinStream's name. */
    virtual const char *Name() const;
    /** Get whether or not this BinStream is cached. Interestingly only overwritten in
     * ChunkStream. */
    virtual bool Cached() const { return false; }
    /** Get this BinStream's current platform (Xbox, PS3, etc). Interestingly only
     * overwritten in ChunkStream. */
    virtual Platform GetPlatform() const { return kPlatformNone; }
    /** The specific implementation for reading from byte data.
     *  @param [in] data The data to read from.
     *  @param [in] bytes The number of bytes to read.
     */
    virtual void ReadImpl(void *data, int bytes) = 0;
    /** The specific implementation for writing to byte data.
     *  @param [in] data The data to write to.
     *  @param [in] bytes The number of bytes to read.
     */
    virtual void WriteImpl(const void *data, int bytes) = 0;
    /** The specific implementation for seeking within this BinStream.
     *  @param [in] offset The offset in the data to seek to.
     *  @param [in] type The Seek type.
     */
    virtual void SeekImpl(int offset, SeekType type) = 0;

    /** Whether or not the stream uses little endian. */
    bool mLittleEndian; // 0x4
    /** PRNG source, used for encryption */
    Rand2 *mCrypto; // 0x8

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
    void ReadString(char *out, int len);

    BinStream &operator>>(Symbol &);
    BinStream &operator>>(class String &);

    /** Enables read encryption for e.g. archives.
     * Enables read encryption using Rand2, used in .dtb and .ark files.
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
    void Read(void *out, int len);

    /** Write `len` bytes from the current BinStream position, into the `data` buffer.
     * @param [out] data The pointer to write data into.
     * @param [in] len The length of data to write.
     */
    void Write(const void *data, int len);

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
    void ReadEndian(void *out, int len);

    /** Writes `len` bytes of data into `data`, reversed if mLittleEndian is true.
     *
     * @param [out] out The pointer to write data into.
     * @param [in] len The length of data to write.
     */
    void WriteEndian(const void *data, int len);

    bool LittleEndian() const { return mLittleEndian; }
    bool UseLittleEndian(bool use) {
        mLittleEndian = use;
        return mLittleEndian;
    }

    BS_WRITE_OP(short);
    BS_WRITE_OP(unsigned short);
    BS_WRITE_OP(int);
    BS_WRITE_OP(unsigned int);
    BS_WRITE_OP(long);
    BS_WRITE_OP(unsigned long);
    BS_WRITE_OP(long long);
    BS_WRITE_OP(unsigned long long);
    BS_WRITE_OP(float);

    BinStream &operator<<(char c) {
        Write(&c, 1);
        return *this;
    }

    BinStream &operator<<(unsigned char uc) {
        Write(&uc, 1);
        return *this;
    }

    BinStream &operator<<(bool b) {
        unsigned char uc = (b) ? 1 : 0;
        Write(&uc, 1);
        return *this;
    }

    BS_READ_OP(int);
    BS_READ_OP(unsigned int);
    BS_READ_OP(short);
    BS_READ_OP(unsigned short);
    // TODO: if long has a special implementation, chances are unsigned long does too.
    // Comment the macro for unsigned long out, and then refactor all instances of
    // writing to a u32 typedef to writing to an unsigned int instead.
    // BS_READ_OP(long);
    // BS_READ_OP(unsigned long);
    BS_READ_OP(long long);
    BS_READ_OP(unsigned long long);
    BS_READ_OP(float);

    BinStream &operator>>(char &out) {
        Read(&out, 1);
        return *this;
    }

    BinStream &operator>>(unsigned char &out) {
        Read(&out, 1);
        return *this;
    }

    BinStream &operator>>(bool &b) {
        unsigned char uc;
        *this >> uc;
        b = (uc != 0);
        return *this;
    }

    BinStream &operator>>(long &l) {
        long long ll;
        ReadEndian(&ll, sizeof(ll));
        l = ll;
        return *this;
    }

    BS_READ_FUNC(char, Char);
    BS_READ_FUNC(unsigned char, Byte);
    BS_READ_FUNC(short, Short);
    BS_READ_FUNC(unsigned short, UShort);
    BS_READ_FUNC(int, Int);
    BS_READ_FUNC(unsigned int, UInt);
    // BS_READ_FUNC(long, Long);
    // BS_READ_FUNC(unsigned long, ULong);
    BS_READ_FUNC(long long, LongLong);
    BS_READ_FUNC(unsigned long long, ULongLong);
    BS_READ_FUNC(bool, Bool);
    BS_READ_FUNC(float, Float);
};

// Note: `Allocator` here is actually the size/capacity type parameter on Wii.
// The name is based on Xbox 360 symbols, which show the allocator type instead.
template <class T, class Allocator>
BinStream &operator<<(BinStream &bs, const std::vector<T, Allocator> &vec) {
    bs << (int)vec.size();
    for (typename std::vector<T, Allocator>::const_iterator it = vec.begin();
         it != vec.end();
         it++) {
        bs << *it;
    }
    return bs;
}

template <class T, class Allocator>
BinStream &operator>>(BinStream &bs, std::vector<T, Allocator> &vec) {
    unsigned int length;
    bs >> length;
    vec.resize(length);

    for (typename std::vector<T, Allocator>::iterator it = vec.begin(); it != vec.end();
         it++) {
        bs >> *it;
    }

    return bs;
}

template <class T, class Allocator>
BinStream &operator<<(BinStream &bs, const std::list<T, Allocator> &list) {
    bs << list.size();
    FOREACH (it, list) {
        bs << *it;
    }
    return bs;
}

template <class T, class Allocator>
BinStream &operator>>(BinStream &bs, std::list<T, Allocator> &list) {
    unsigned int length;
    bs >> length;
    list.resize(length);

    for (typename std::list<T, Allocator>::iterator it = list.begin(); it != list.end();
         it++) {
        bs >> *it;
    }

    return bs;
}

template <class T1, class T2>
BinStream &operator<<(BinStream &bs, const std::map<T1, T2> &map) {
    bs << map.size();
    for (typename std::map<T1, T2>::const_iterator it = map.begin(); it != map.end();
         ++it) {
        bs << it->first << it->second;
    }
    return bs;
}

template <class T1, class T2>
BinStream &operator>>(BinStream &bs, std::map<T1, T2> &map) {
    int size;
    bs >> size;
    for (; size != 0; size--) {
        T1 key;
        bs >> key;
        bs >> map[key];
    }
    return bs;
}

template <class T1, class T2>
BinStream &operator>>(BinStream &bs, std::pair<T1, T2> &p) {
    bs >> p.first >> p.second;
    return bs;
}

template <class T>
BinStream &operator>>(BinStream &bs, T *t) {
    t->Load(bs);
}
