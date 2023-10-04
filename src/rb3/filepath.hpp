#ifndef RB3_FILEPATH_HPP
#define RB3_FILEPATH_HPP
#include "string.hpp"

class FilePath : String {
public:
	FilePath(const String&);
	FilePath(const char*);
	virtual ~FilePath();

	void fn_8034C91C(const char*, const char*);
};

#endif
