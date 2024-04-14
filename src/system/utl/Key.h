#ifndef UTL_KEY_H
#define UTL_KEY_H
#include <vector>

// thank god for the RB2 dump
template <class T> class Key {
public:
    T value;
    float frame;

    // I found a weak copy ctor and weak operator=(const Key<T>&)
    // not sure if we need to explicitly write these or not
};

// Keys is a vector<Key<T>>
// would make sense for determining what value is at what frame,
// not sure how the second template gets incorporated yet
template <class T1, class T2> class Keys : public std::vector<Key<T1> > {
public:
    // definitely change the return types, I wasn't able to infer them
    void LastFrame() const;
    void Add(const T1&, float, bool);
    void AtFrame(float, const T1*&, const T1*&, float&) const; // very possible this went unused in RB3 in favor of the method directly below this one
    void AtFrame(float, const Key<T1>*&, const Key<T1>*&, float&) const;
};

#endif
