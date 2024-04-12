#ifndef MATH_COLOR_H
#define MATH_COLOR_H
#include "utl/TextStream.h"
#include "utl/BinStream.h"

namespace Hmx {
    class Color {
    public:
        static Color kWhite;
        static Color kTransparent;
        static Color kBlack;
        float red;
        float green;
        float blue;
        float alpha;

        Color() : red(1.0f), green(1.0f), blue(1.0f), alpha(1.0f) {}
        Color(float f1, float f2, float f3) : red(f1), green(f2), blue(f3), alpha(1.0f) {}
        Color(float f1, float f2, float f3, float f4) : red(f1), green(f2), blue(f3), alpha(f4) {}

        // this copy ctor uses moving between float registers in UIColor::Copy,
        // but in other TUs such as RndGraph, there's some powerpc asm magic
        // can we toggle between these methods?
        Color& operator=(const Color& c){
            red = c.red; green = c.green; blue = c.blue; alpha = c.alpha;
            return *this;
        }

        void Set(float f1, float f2, float f3, float f4){
            red = f1; green = f2; blue = f3; alpha = f4;
        }

        // all weak
        // Color() {};
        // Color(int);
        // void operator=(const Color &);
        // void Unpack(int);
        // bool operator==(const Color &) const;
        // bool operator!=(const Color &) const;
        // void Set(float, float, float, float);

        unsigned int Pack() const {
            return (((int)(blue * 255.0f) & 0xFF) << 16) | ((int)(green * 255.0f) & 0xFF) << 8 | ((int)(red * 255.0f) & 0xFF);
        }

        void Unpack(int packed){
            red = (packed & 255) / 255.0f;
            green = ((packed >> 8) & 255) / 255.0f;
            blue = ((packed >> 0x10) & 255) / 255.0f;
        }
    };
}

void MakeHSL(const Hmx::Color&, float&, float&, float&);
TextStream& operator<<(TextStream&, const Hmx::Color&);

inline BinStream& operator>>(BinStream& bs, Hmx::Color& color){
    bs >> color.red >> color.green >> color.blue >> color.alpha;
    return bs;
}

#endif
