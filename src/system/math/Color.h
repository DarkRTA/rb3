#ifndef MATH_COLOR_H
#define MATH_COLOR_H
#include "types.h"
#include "utl/TextStream.h"
#include "utl/BinStream.h"
#include "math/MathFuncs.h"
#include "decomp.h"

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

        // copy ctor uses asm magic
        Color(const register Color& color){
            register Color* theCol = this;
            register float temp1;
            register float temp2;
            ASM_BLOCK(
                psq_lx temp2,0,color,0,0
                psq_l temp1,8(color),0,0
                psq_stx temp2,0,theCol,0,0
                psq_st temp1,8(theCol),0,0
            )
        }

        // assignment operator does not
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

        void Set(float f){ red = green = blue = alpha = f; }

        void Set(float r, float g, float b){
            red = r; green = g; blue = b;
        }

        int Pack() const {
            return (((int)(blue * 255.0f) & 0xFF) << 16) | ((int)(green * 255.0f) & 0xFF) << 8 | ((int)(red * 255.0f) & 0xFF);
        }

        void Unpack(int packed){
            red = (packed & 255) / 255.0f;
            green = ((packed >> 8) & 255) / 255.0f;
            blue = ((packed >> 0x10) & 255) / 255.0f;
        }

        Color& operator *=(float f) {
            red *= f;
            green *= f;
            blue *= f;
            alpha *= f;
            return *this;
        }
    };

    class Color32 {
        union {
            uint x;
            struct {
                u8 a, b, g, r;
            };
        };
        public:
        inline void Clear() { x = -1; }
        float fr() const { return r * 0.0039215688593685627f;}
        float fg() const { return g * 0.0039215688593685627f;}
        float fb() const { return b * 0.0039215688593685627f;}
        float fa() const { return a * 0.0039215688593685627f;}
    };
}

void MakeHSL(const Hmx::Color&, float&, float&, float&);
TextStream& operator<<(TextStream&, const Hmx::Color&);

inline BinStream& operator>>(BinStream& bs, Hmx::Color& color){
    bs >> color.red >> color.green >> color.blue >> color.alpha;
    return bs;
}

inline void Add(const Hmx::Color& c1, const Hmx::Color& c2, Hmx::Color& res){
    float alpha = c1.alpha + c2.alpha;
    res.blue = c1.blue + c2.blue;
    res.green = c1.green + c2.green;
    res.red = c1.red + c2.red;
    res.alpha = alpha;
}

inline void Subtract(const Hmx::Color& c1, const Hmx::Color& c2, Hmx::Color& res){
    float alpha = c1.alpha - c2.alpha;
    res.blue = c1.blue - c2.blue;
    res.green = c1.green - c2.green;
    res.red = c1.red - c2.red;
    res.alpha = alpha;
}

inline Hmx::Color& Average(Hmx::Color& res, const Hmx::Color& c1, const Hmx::Color& c2){
    res.Set((c1.red + c2.red) / 2, (c1.green + c2.green) / 2, (c1.blue + c2.blue) / 2, (c1.alpha + c2.alpha) / 2);
    return res;
}

inline void Interp(const Hmx::Color& c1, const Hmx::Color& c2, float f, Hmx::Color& res){
    res.Set(Interp(c1.red,c2.red,f), Interp(c1.green,c2.green,f), Interp(c1.blue,c2.blue,f), Interp(c1.alpha,c2.alpha,f));
}

#endif
