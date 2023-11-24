#ifndef RB3_MAKESTRING_HPP
#define RB3_MAKESTRING_HPP
#include "formatstring.hpp"

template <class T>
const char* MakeString(const char* c, T t){
	FormatString fs(c);
	fs << t;
	return fs.Str();
}

template <class T1, class T2>
const char* MakeString(const char* c, T1 t1, T2 t2){
    FormatString fs(c);
	fs << t1 << t2;
	return fs.Str();
}

#endif
