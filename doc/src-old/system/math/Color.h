#ifndef MATH_COLOR_H
#define MATH_COLOR_H

namespace Hmx {
    class Color {
    public:
        float red;
        float green;
        float blue;
        float alpha;
        // all weak
        Color() {};
        Color(int);
        void operator=(const Color &);
        void Unpack(int);
        bool operator==(const Color &) const;
        bool operator!=(const Color &) const;
        void Set(float, float, float, float);

        unsigned int Pack() const {
            return (((int)(blue * 255.0f) & 0xFF) << 16) | ((int)(green * 255.0f) & 0xFF) << 8 | ((int)(red * 255.0f) & 0xFF);
        }
    };
}

#endif
