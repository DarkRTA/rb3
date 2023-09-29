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
	void fn_80362260(unsigned int); // fn_80362260
	void Reserve(unsigned int); // fn_80361C90
	void fn_80361F04(const char *); // fn_80361F04
	void fn_80361F88(String *); // fn_80361F88
	void fn_80361FC4(char); // fn_80361FC4
	void fn_803620B4(char **); // fn_803620B4

	bool AreStringsDifferent(const char *); // fn_80362144
	bool AreStringsDifferent(const String *); // fn_80362188
	bool AreStringsIdentical(const char *); // fn_803621BC
	bool AreStringsIdentical(const String *); // fn_80362200
	int FindIndexOfSubstring(const char *, int); // fn_803622F8
	int FindLastIndexOfChar(char); // fn_803623A0
	int fn_803623E8(char *); // fn_803623E8
	bool SubstrExistsInString(char *); // fn_80362530
	void ReplaceCharsInString(char, char); // fn_80362778
	void SwapStrings(String *); // fn_803627A8
	int FindFirstIndexOfCharAtOffset(char, int); // fn_803622A4
	void fn_80362730(); // fn_80362730

	String *operator=(const char *);
	void ToLower();
	virtual ~String();
	virtual void fn_80361E34();
};

#endif
