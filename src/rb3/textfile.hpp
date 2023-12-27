#ifndef RB3_TEXTFILE_HPP
#define RB3_TEXTFILE_HPP
#include "symbol.hpp"
#include "textstream.hpp"
#include "hmx/object.hpp"

class TextFile : public Hmx::Object, TextStream {
public:
    int unk20;
    
    TextFile();
};

// struct TextFile : TextStream {
//     virtual void virt1();
//     int unk20;
//     TextFile();
//     static Symbol StaticClassName();
// };
#endif
