#ifndef UTL_KEY_H
#define UTL_KEY_H
#include <vector>

// thank god for the RB2 dump
template <class T> class Key {
public:
    T value;
    float frame;
};

// I now think Keys is a vector<Key<T>>
// would make sense for determining what value is at what frame,
// not sure how the second template gets incorporated yet
template <class T1, class T2> class Keys : public std::vector<Key<T1> > {
public:

};

#endif
