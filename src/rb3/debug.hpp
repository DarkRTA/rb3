#ifndef RB3_DEBUG_HPP
#define RB3_DEBUG_HPP
#include "textstream.hpp"


/** Implements most debugging features, such as printing to the console's text output and handling error checking & failure */
class Debug : public TextStream {
public:
    Debug();
    virtual ~Debug(); // fn_802F97E0

    /** Prints to the console's stdout */
    virtual void Print(const char *); // fn_802F96F8

    char unk4, unk5, unk6, unk7, unk8;
    int unkc, unk10, unk14, unk18;
};

#endif
