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
	String(unsigned int, char); // fn_80361D1C

	unsigned int GetTextLength(); // fn_800A6E18
	const char *GetText() const; // fn_8000DB9C
	void CreateEmptyString(unsigned int); // fn_80362260
	void Reserve(unsigned int); // fn_80361C90
	String* AppendString(const char *); // fn_80361F04
	String* AppendString(String *); // fn_80361F88
	String* AppendChar(char); // fn_80361FC4
	String* operator=(const char **); // fn_803620B4
	String* CopyString(String*); // fn_803620BC
	int FindFirstIndexOfChar(char); // fn_803622E4
	int FindIndexOfSubstringStrStr(char*); // fn_803622F0
	int FindFirstOf(char*, int); // fn_8036233C
	char* GetTextAtOffset(int); // fn_80362110
	String* fn_80361E38(String, const char*); // fn_80361E38
	String* fn_80361E7C(String, char); // fn_80361E7C
	String* fn_80361EC0(String, String*); // fn_80361EC0

	String CreateSubstringFromString(unsigned int, unsigned int) const; // fn_8036266C
	String CreateSubstringFromString(unsigned int); // fn_80362660
	String* ClearString(); // fn_803628F8
	String* TruncateString(unsigned int); // fn_80362908

	char GetCharFromBackIndex(int); // fn_8036211C
	char* GetSubstrFromBackIndex(int); // fn_80362130
	bool IsThisStrLessThan(String*) const; // fn_80362234
	int FindIndexOfSubstring(char*); // fn_80362478

	bool AreStringsDifferent(const char *); // fn_80362144
	bool AreStringsDifferent(const String *); // fn_80362188
	bool AreStringsIdentical(const char *); // fn_803621BC
	bool AreStringsIdentical(const String *); // fn_80362200
	int FindIndexOfSubstringAtOffset(const char *, int); // fn_803622F8
	int FindLastIndexOfChar(char) const; // fn_803623A0
	int FindLastOf(char *) const; // fn_803623E8
	bool SubstrExistsInString(char *); // fn_80362530
	void ReplaceCharsInString(char, char); // fn_80362778
	void SwapStrings(String *); // fn_803627A8
	int FindFirstIndexOfCharAtOffset(char, int); // fn_803622A4
	void fn_80362730(); // fn_80362730

	String *operator=(const char *);
	void ToLower();
	virtual ~String();
	virtual String* VirtuallyAppendString(const char*); // fn_80361E34
};

#endif
