#ifndef EC_CONTENT_H
#define EC_CONTENT_H

#include <ec/asyncOp.h>
#include <ec/vector.h>
#include <MSL_C++/string>


namespace ec {
    ECResult downloadUcsFule(const ECAsyncOpEnv &, const ECString &, char *, unsigned char *, unsigned long &);
    class Buffer {
        ~Buffer();
    };
    template <class T>
    class Content {
        u8 pad[0xf];
        //ECString has a size of 0xc
        ECString str1; //0x10
        ECString str2; //0x1c
        ECString str3; //0x28
        u8 pad1[0x4];
        ECString str4; //0x38
        ECString str5; //0x44
        ECString str6; //0x50
        ~Content();
        void get();
    };
    struct ECTmdView {};
    struct ECWhichContents {};
    struct ECTitleContentsResources {};
    ECResult getTmd(const ECAsyncOpEnv &, const ECString &, unsigned short *, unsigned char *&, unsigned long &, unsigned char *&, unsigned long &);
    ECResult importTmd(const ECAsyncOpEnv &, unsigned char *, unsigned long, unsigned char *, unsigned long, unsigned char *, unsigned long);
    ECResult getTitleContentsResources(const ECAsyncOpEnv&, const ECTmdView&, unsigned char*, unsigned long, ECWhichContents, ECWhichContents, unsigned short*, unsigned long, bool*, bool*, unsigned short*, unsigned long*, unsigned short*, unsigned long*, unsigned long*, ECTitleContentsResources*, ECTitleContentsResources*);
    ECResult importContents(const ECAsyncOpEnv&, const ECTmdView&, unsigned char*, unsigned long, unsigned char*, unsigned long, unsigned char*, unsigned long, unsigned short*, unsigned long);
    ECResult importContent(const ECAsyncOpEnv&, unsigned long long, unsigned long, unsigned long, unsigned char*, unsigned long);
    class ImportBuf {
        ~ImportBuf();
        void close();
        void write(const char*, unsigned long);
    };
    ECResult importTickets(const ECAsyncOpEnv&, const ECVector<ECString>&, const ECString&, const void*, unsigned long);
    ECResult importTicket(const ECAsyncOpEnv&, const void*, const void*, unsigned long, const void*, unsigned long);
    ECResult importCommonTicket(const ECAsyncOpEnv&, const ECString&, unsigned char*, unsigned long&);
    ECResult downloadSysTitle(const ECAsyncOpEnv&, unsigned long long, unsigned long);


}

#endif