#ifndef MATH_COLOR_H
#define MATH_COLOR_H
#include "utl/TextStream.h"

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

        Color(float f1, float f2, float f3) : red(f1), green(f2), blue(f3), alpha(1.0f) {}
        Color(float f1, float f2, float f3, float f4) : red(f1), green(f2), blue(f3), alpha(f4) {}

        // all weak
        // Color() {};
        // Color(int);
        // void operator=(const Color &);
        // void Unpack(int);
        // bool operator==(const Color &) const;
        // bool operator!=(const Color &) const;
        // void Set(float, float, float, float);

        // unsigned int Pack() const {
        //     return (((int)(blue * 255.0f) & 0xFF) << 16) | ((int)(green * 255.0f) & 0xFF) << 8 | ((int)(red * 255.0f) & 0xFF);
        // }
    };
}

void MakeHSL(const Hmx::Color&, float&, float&, float&);
TextStream& operator<<(TextStream&, const Hmx::Color&);

#endif
