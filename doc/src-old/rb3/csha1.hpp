#ifndef RB3_CSHA1_HPP
#define RB3_CSHA1_HPP

class CSHA1 {
public:
    CSHA1();
    ~CSHA1();
    void Reset();
    void Transform(unsigned long *, unsigned const char *);
    void Update(unsigned const char *, unsigned long);
    void Final();
    void GetHash(unsigned char *) const;
};

#endif
