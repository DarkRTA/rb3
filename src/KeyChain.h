#ifndef RB3_KEYCHAIN_H
#define RB3_KEYCHAIN_H

class KeyChain {
public:
    static void getMasher(unsigned char*);
    static void getKey(int, unsigned char*, unsigned char*);
    static int getNumKeys();
};

#endif
