#pragma once

class KeyChain {
public:
    static void getMasher(unsigned char *);
    static void getKey(int, unsigned char *, unsigned char *);
    static int getNumKeys();
};
