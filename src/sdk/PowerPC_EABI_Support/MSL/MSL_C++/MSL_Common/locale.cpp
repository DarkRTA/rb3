#include <MSL_C++/locale>
#include <MSL_C++/stdexcept>
#include "decomp.h"

std::locale::id std::ctype<char>::id;
std::locale::id std::ctype<wchar_t>::id;

std::locale::id std::codecvt<char, char, int>::id;
std::locale::id std::codecvt<wchar_t, char, int>::id;

DECOMP_FORCEFUNC(locale, std::logic_error, what())
DECOMP_FORCEBLOCK(locale, (), throw std::logic_error("");)
DECOMP_FORCEBLOCK(locale, (), throw std::length_error("");)
DECOMP_FORCEBLOCK(locale, (), throw std::out_of_range("");)
