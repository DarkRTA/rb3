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
	void reserve(unsigned int); // fn_80361C90
	String(unsigned int, char); // fn_80361D1C

	virtual ~String();
	virtual void Print(const char*); // fn_80361E34

	String operator+(const char*) const; // fn_80361E38
	String operator+(char); // fn_80361E7C
	String operator+(String*); // fn_80361EC0
	String* operator+=(const char *); // fn_80361F04
	String* operator+=(const String&); // fn_80361F88
	String* operator+=(char); // fn_80361FC4
	String *operator=(const char *);
	String* operator=(const char **); // fn_803620B4
	String* operator=(const String&); // fn_803620BC
	
	char* operator[](unsigned int); // fn_80362110
	char rcharAt(int); // fn_8036211C
	char* rindex(int); // fn_80362130
	bool operator!=(const char *) const; // fn_80362144
	bool operator!=(const String&) const; // fn_80362188
	bool operator==(const char *) const; // fn_803621BC
	bool operator==(const String&) const; // fn_80362200
	bool operator<(const String&) const; // fn_80362234
	void resize(unsigned int); // fn_80362260
	int find(char, int); // fn_803622A4
	int find(char); // fn_803622E4
	int find(const char*) const; // fn_803622F0
	int find(const char *, unsigned int) const; // fn_803622F8
	int find_first_of(const char*, unsigned int) const; // fn_8036233C
	int find_last_of(char) const; // fn_803623A0
	int find_last_of(const char *) const; // fn_803623E8
	int rfind(const char*) const; // fn_80362478
	bool contains(const char *) const; // fn_80362530

	// TODO: figure out what this does
	void fn_80362560(char*, String*); // fn_80362560
	
	String substr(unsigned int); // fn_80362660
	String substr(unsigned int, unsigned int) const; // fn_8036266C
	void ToLower();
	void ToUpper(); // fn_80362730
	void ReplaceAll(char, char); // fn_80362778
	void swap(String&); // fn_803627A8
	String* replace(unsigned int, unsigned int, const char*); // fn_803627CC
	String* erase(); // fn_803628F8
	String* erase(unsigned int); // fn_80362908
	void erase(unsigned int, unsigned int); // fn_80362924
	String* insert(int, unsigned int, char ); // fn_80362930
	String* replace(unsigned int, const char*); // fn_803629F4
	String* replace(unsigned int, String*); // fn_80362A00

	// symbols found in RB2:
	// empty__6StringCFv, npos__6String, __ct__6StringF6Symbol, __as__6StringF6Symbol, find_first_of__6StringCFPCc

	// probably inline header methods
	unsigned int length(); // fn_800A6E18
	bool IsTextLengthZero(); // fn_800AFE60
	const char *c_str() const; // fn_8000DB9C
	void fn_801CEDFC(String*);	
};

#endif
