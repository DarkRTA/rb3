#ifndef RB3_FILEPATH_HPP
#define RB3_FILEPATH_HPP
#include "string.hpp"

class FilePath : String {
public:
	FilePath(const String &); // fn_8000EC00
	FilePath(const char *); // fn_8000EC5C
	virtual ~FilePath(); // fn_8000EA28

	void Set(const char *, const char *); // fn_8034C91C
	FilePath* operator=(const FilePath&);
};

#endif
