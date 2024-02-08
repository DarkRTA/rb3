#ifndef RB3_STRING_HPP
#define RB3_STRING_HPP
#include "TextStream.h"
#include "symbol.hpp"

/** An object representing a sequence of characters. */
class String : public TextStream {
public:
    /** The length of the character sequence. */
    unsigned int len;
    /** The character sequence itself. */
    char *text;

    /** Represents "NULL" or "not found" when searching for particular characters or substrings in a string. */
    static int npos;

    String();
    String(const char *);
    String(Symbol); // fn_80361BC0
    String(const String &);
    String(unsigned int, char); // fn_80361D1C

    virtual ~String();
    virtual void Print(const char *); // fn_80361E34

    /** Allocates an inputted number of bytes for the String to hold its character sequence.
     *  @param [in] num The number of bytes to reserve.
    */
    void reserve(unsigned int num); // fn_80361C90

    String operator+(const char *) const; // fn_80361E38
    String operator+(char); // fn_80361E7C
    String operator+(String *); // fn_80361EC0
    String *operator+=(const char *); // fn_80361F04
    String *operator+=(const String &); // fn_80361F88
    String *operator+=(char); // fn_80361FC4
    String *operator=(const char *);
    String *operator=(Symbol); // fn_803620B4
    String *operator=(const String &); // fn_803620BC

    /** Returns a pointer to the character sequence at the supplied index.
     * @param [in] idx The index of the character sequence in which to return a pointer.
    */
    char *operator[](unsigned int idx); // fn_80362110

    /** Retrieves a character from the String, from the end of the sequence.
     * @param [in] idx The index from the end of the sequence in which to retrieve the char. Note that this MUST be a negative number between -1 and -(the length of the string).
    */
    char rcharAt(int idx); // fn_8036211C

    /** Returns a pointer to the character sequence at the supplied index, from the end of the sequence.
     * @param [in] idx The index from the end of the sequence in which to retrieve the pointer. Note that this MUST be a negative number between -1 and -(the length of the string).
    */
    char *rindex(int idx); // fn_80362130

    bool operator!=(const char *) const; // fn_80362144
    bool operator!=(const String &) const; // fn_80362188
    bool operator==(const char *) const; // fn_803621BC
    bool operator==(const String &) const; // fn_80362200
    bool operator<(const String &) const; // fn_80362234

    /** Resizes the buffer containing the String's character sequence.
     *  @param [in] bytes The desired number of bytes to make the buffer.
    */
    void resize(unsigned int bytes); // fn_80362260

    /** Searches for the first instance of a character in the String from a particular offset. 
     * @param [out] out The index where the character was found. If it was NOT found, this value will be -1.
     * @param [in] c The character to search for.
     * @param [in] idx The index of the String from which to begin searching.
    */
    int find(char c, int idx); // fn_803622A4

    /** Searches for the first instance of a character in the String. 
     * @param [out] out The index where the character was found. If it was NOT found, this value will be -1.
     * @param [in] c The character to search for.
    */
    int find(char c); // fn_803622E4

    /** Searches for the first instance of a substring in the String. 
     * @param [out] out The index where the substring was found. If it was NOT found, this value will be -1.
     * @param [in] str The substring to search for.
    */
    int find(const char * str) const; // fn_803622F0

    /** Searches for the first instance of a substring in the String from a particular offset. 
     * @param [out] out The index where the substring was found. If it was NOT found, this value will be -1.
     * @param [in] str The substring to search for.
     * @param [in] idx The index of the String from which to begin searching.
    */
    int find(const char * str, unsigned int idx) const; // fn_803622F8

    /** Searches for the first instance of ANY character in the inputted substring, in the String from a particular offset. 
     * @param [out] out The index where ANY character in the substring was found. If it was NOT found, this value will be -1.
     * @param [in] str The sequence of characters to search for.
     * @param [in] idx The index of the String from which to begin searching.
    */
    int find_first_of(const char * str, unsigned int idx) const; // fn_8036233C

    /** Searches for the last instance of a character in the String. 
     * @param [out] out The index where the character was found. If it was NOT found, this value will be -1.
     * @param [in] c The character to search for.
    */
    int find_last_of(char c) const; // fn_803623A0

    /** Searches for the last instance of ANY character in the inputted substring, in the String. 
     * @param [out] out The index where ANY character in the substring was found. If it was NOT found, this value will be -1.
     * @param [in] str The sequence of characters to search for.
    */
    int find_last_of(const char * str) const; // fn_803623E8

    int rfind(const char *) const; // fn_80362478

    /** Determines if the inputted substring is contained inside the String. 
     * @param [out] out TRUE if the inputted substring was found inside the String, FALSE otherwise.
     * @param [in] str The substring to search for.
    */
    bool contains(const char * str) const; // fn_80362530

    // TODO: figure out what this does
    // void fn_80362560(char *, UnknownJsonConverterMember *); // fn_80362560

    /** Creates a new String, where the character sequence is this String's character sequence beginning at a particular index.
     * @param [out] out The new String.
     * @param [in] idx The index of this String's character sequence, from which to make the new String's character sequence.
    */
    String substr(unsigned int idx); // fn_80362660

    /** Creates a new String, where the character sequence is a particular number of characters from this String's character sequence, beginning at a particular index.
     * @param [out] out The new String.
     * @param [in] idx The index of this String's character sequence, from which to make the new String's character sequence.
     * @param [in] new_len The desired length of the new String's character sequence.
    */
    String substr(unsigned int idx, unsigned int new_len) const; // fn_8036266C

    /** Converts all characters of the String to lowercase, according to the current locale. */
    void ToLower();

    /** Converts all characters of the String to uppercase, according to the current locale. */
    void ToUpper(); // fn_80362730

    /** Replaces all instances of one character in a String with another.
     * @param [in] old_char The character to be replaced.
     * @param [in] new_char The character to replace old_char with.
    */
    void ReplaceAll(char old_char, char new_char); // fn_80362778

    /** Swaps the contents of this String with the supplied String.
     * @param [in] s The String to swap with.
    */
    void swap(String & s); // fn_803627A8

    /** Replaces this String's text with the contents of a supplied buffer.
     * @param [in] idx: The starting index of the text you want to replace.
     * @param [in] new_len: The desired number of characters to replace.
     * @param [in] buf: The series of characters which you are replacing with.
    */
    String *replace(unsigned int idx, unsigned int new_len, const char * buf); // fn_803627CC

    /** Clears the contents of the String's character sequence. */
    String *erase(); // fn_803628F8

    /** Clears the contents of the String's character sequence after the supplied index.
     * @param [in] idx: The index from which to erase the String's character sequence.
    */
    String *erase(unsigned int); // fn_80362908

    /** Clears a set number of characters of the String's character sequence after the supplied index.
     * @param [in] idx: The index from which to erase the String's character sequence.
     * @param [in] erase_len: The desired number of characters to have erased.
    */
    void erase(unsigned int idx, unsigned int erase_len); // fn_80362924

    /** Inserts the supplied character into this String's character sequence at a particular index, a set number of times. 
     * @param [in] idx: The index from which to begin inserting the character.
     * @param [in] cnt: How many times the character should be inserted.
     * @param [in] c: The character to insert.
    */
    String *insert(int idx, unsigned int cnt, char c); // fn_80362930

    /** Replaces this String's text with the contents of a supplied buffer at a given index.
     * @param [in] idx: The starting index of the text you want to replace.
     * @param [in] buf: The series of characters which you are replacing with.
    */
    String *replace(unsigned int idx, const char * buf); // fn_803629F4

    /** Replaces this String's text with another String's text at a given index.
     * @param [in] idx: The starting index of the text you want to replace.
     * @param [in] str: The String whose text you are replacing with.
    */
    String *replace(unsigned int idx, String * str); // fn_80362A00

    // symbols found in RB2:
    // npos__6String, find_first_of__6StringCFPCc

    // probably inline header methods
    unsigned int length() const; // fn_800A6E18
    const char *c_str() const; // fn_8000DB9C
    bool empty() const; // fn_8000EC3C
    // fn_8000DAC4
};

bool SearchReplace(const char *, const char *, const char *, char *);
bool StrNCopy(char *, const char *, int);

#endif
