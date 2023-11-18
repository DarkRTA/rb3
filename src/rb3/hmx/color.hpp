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
        void operator=(const Color&);
        unsigned int Pack() const;
        void Unpack(int);
        bool operator==(const Color&) const;
        bool operator!=(const Color&) const;
        void Set(float, float, float, float);
    };
}

#endif
