#ifndef QUAZAL_QRESULT_HPP
#define QUAZAL_QRESULT_HPP

namespace Quazal {
    class qResult {
    public:
        int i1;
        char* c;
        int i2;

        qResult();
        qResult(const int&);
        bool Equals(const int&) const;
        bool Equals(const bool&) const;
        operator bool() const;
        qResult* operator=(const int&);
        qResult* operator=(const qResult&);
        void Trace(unsigned int) const;
    };
}

#endif