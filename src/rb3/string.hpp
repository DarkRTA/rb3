#ifndef RB3_STRING_HPP
#define RB3_STRING_HPP
#include "textstream.hpp"

class String : TextStream {
public:
	unsigned int len;
	char *text;
	
	String();
	String(const char *);
	String(const char **); // fn_80361BC0
	String(const String &);
	void Reserve(unsigned int); // fn_80361C90
	String(unsigned int, char); // fn_80361D1C

	virtual ~String();
	virtual String* VirtualAppend(const char*); // fn_80361E34

	String operator+(const char*); // fn_80361E38
	String operator+(char); // fn_80361E7C
	String operator+(String*); // fn_80361EC0
	String* operator+=(const char *); // fn_80361F04
	String* operator+=(String *); // fn_80361F88
	String* operator+=(char); // fn_80361FC4
	String *operator=(const char *);
	String* operator=(const char **); // fn_803620B4

	String* CopyString(String*); // fn_803620BC
	char* GetTextAtOffset(int); // fn_80362110
	char GetCharFromBackIndex(int); // fn_8036211C
	char* GetSubstrFromBackIndex(int); // fn_80362130
	bool AreStringsDifferent(const char *); // fn_80362144
	bool AreStringsDifferent(const String *); // fn_80362188
	bool AreStringsIdentical(const char *); // fn_803621BC
	bool AreStringsIdentical(const String *); // fn_80362200
	bool IsThisStrLessThan(String*) const; // fn_80362234
	void CreateEmptyString(unsigned int); // fn_80362260
	int FindFirstIndexOfCharAtOffset(char, int); // fn_803622A4
	int FindFirstIndexOfChar(char); // fn_803622E4
	int FindIndexOfSubstringStrStr(char*); // fn_803622F0
	int FindIndexOfSubstringAtOffset(const char *, int); // fn_803622F8
	int FindFirstOf(char*, int); // fn_8036233C
	int FindLastIndexOfChar(char) const; // fn_803623A0
	int FindLastOf(char *) const; // fn_803623E8
	int FindIndexOfSubstring(char*); // fn_80362478
	bool SubstrExistsInString(char *); // fn_80362530

	// TODO: figure out what this does
	void fn_80362560(char*, String*); // fn_80362560
	
	String CreateSubstringFromString(unsigned int); // fn_80362660
	String CreateSubstringFromString(unsigned int, unsigned int) const; // fn_8036266C
	void ToLower();
	void fn_80362730(); // fn_80362730
	void ReplaceCharsInString(char, char); // fn_80362778
	void SwapStrings(String *); // fn_803627A8
	String* ReplaceTextAtIndex(unsigned int, unsigned int, const char*); // fn_803627CC
	String* ClearString(); // fn_803628F8
	String* TruncateString(unsigned int); // fn_80362908
	String* ReplaceTextAtIndexWithLabel(unsigned int, unsigned int); // fn_80362924
	String* InsertCharAtIndex(int, unsigned int, char ); // fn_80362930
	String* ReplaceTextAtIndex(unsigned int, const char*); // fn_803629F4
	String* ReplaceTextAtIndex(unsigned int, String*); // fn_80362A00

	// probably inline header methods
	unsigned int GetStrLen(); // fn_800A6E18
	bool IsTextLengthZero(); // fn_800AFE60
	const char *GetText() const; // fn_8000DB9C
	void fn_801CEDFC(String*);	
};

#endif
