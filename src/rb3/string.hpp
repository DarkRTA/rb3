#ifndef RB3_STRING_HPP
#define RB3_STRING_HPP
#include "textstream.hpp"

class String : TextStream {
public:
	unsigned int len;
	char *text;
	String();
	String(const char *);
	String(const String &);

	const char *GetText() const; // fn_8000DB9C
	// void fn_80362260(int); // fn_80362260
	// void fn_80361C90(int); // fn_80361C90

	void operator=(const char *);
	void ToLower();
	virtual ~String();
	virtual void fn_80361E34();
};

#endif
