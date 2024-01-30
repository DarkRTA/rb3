#ifndef HMX_COLOR_HPP
#define HMX_COLOR_HPP

namespace Hmx {
    class Color {
    public:
        float red;
        float green;
        float blue;
        float alpha;

        Color() {};
        Color(int);
        void operator=(const Color &);
        void Unpack(int);
        bool operator==(const Color &) const;
        bool operator!=(const Color &) const;
        void Set(float, float, float, float);

        unsigned int Pack() const {
            return ((int)(blue * 255.0f) & 0xFFU) | ((int)(green * 255.0f) & 0xFFU) << 8 | ((int)(red * 255.0f) & 0xFFU) << 0x10;
        }
    };
}

#endif