#ifndef RB3_BINSTREAM_HPP
#define RB3_BINSTREAM_HPP
#include "symbol.hpp"
#include "string.hpp"
#include "rand2.hpp"

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
        SeekMode0, /**< SeekMode0 (probably SEEK_SET)*/
        SeekMode1, /**< SeekMode1 (probably SEEK_CUR)*/
        SeekMode2  /**< SeekMode2 (probably SEEK_END)*/
    };

    BinStream(bool);
    virtual ~BinStream();
    virtual void Flush() = 0;
    virtual int Tell() = 0;
    virtual bool Eof() = 0;
    virtual bool Fail() = 0;
    virtual const char *Name() const; // fn_80342ACC
    virtual int Cached() {
        return 0;
    } // links to fn_8077BAA0, which returns 0
    virtual int GetPlatform() {
        return 0;
    } // links to fn_8077BAA0, which returns 0
    virtual void ReadImpl(void *, int) = 0;
    virtual void WriteImpl(const void *, int) = 0;
    virtual void SeekImpl(
        int,
        SeekType
    ) = 0;
    /** Endianness flags, denotes whether to swap from native. (guess) */
    bool unk04;
    /** PRNG source, used for encryption */
    Rand2 *mCrypto;

    // taken from RB2
    BinStream &operator<<(const char *);
    BinStream &operator<<(const Symbol &);
    BinStream &operator<<(const String &);
    BinStream &operator>>(Symbol &);
    BinStream &operator>>(String &);

    void WriteEndian(const void *, int);
    void Write(const void *, int);

    /** Reads a `len` length string to `out`.
     * Reads a standard C string of length `len` into `out` from
     * the open file.
     *
     * @param [out] out The pointer to read the string into.
     * @param [in] len The length of text to read.
     */
    void ReadString(char * out, int len);

    /** Reads `len` bytes of data, backwards, into `out`.
     * Reads a length of data specified by `len` from the open file
     * into `out`, using the reverse endianness.
     * (PPC == BE, therefore reverse == LE)
     *
     * @param [out] out The pointer to read data into.
     * @param [in] len The length of data to read.
     */
    void ReadEndian(void * out, int len);

    /** Reads `len` bytes of data into `out`.
     * Reads a length of data specified by `len` from the open file
     * into `out`, using the native endianness (PPC == BE).
     *
     * @param [out] out The pointer to read data into.
     * @param [in] len The length of data to read.
     */
    void Read(void * out, int len);

    /** Enables read encryption for e.g. archives.
     * Enables read encryption, used for things such as archives.
     */
    void EnableReadEncryption();

    /** Enables write encryption using `key` as the PRNG seed.
     * @param [in] key Key to use. */
    void EnableWriteEncryption(int key);
    void DisableEncryption();

    /** Seeks to `offset` using `mode`. */
    void Seek(int offset, SeekType mode);

    // not taken from RB2, found in the asm
    BinStream &operator<<(unsigned int); // fn_800A7638
    BinStream &operator>>(unsigned int &); // fn_800A77B4
    BinStream &operator>>(float &); // fn_800A77B4 also, because code merging
    BinStream &operator>>(unsigned char &); // fn_800A7730
    BinStream &operator>>(bool &); // fn_800A7764
    BinStream &operator<<(char); // fn_800A75FC
    BinStream &operator<<(short); // fn_801CB744
    BinStream &operator>>(short &); // fn_801CCA70
    BinStream &operator<<(float); // fn_800B95C4
};

#endif
