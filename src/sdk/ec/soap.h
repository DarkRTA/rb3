#ifndef EC_SOAP_H
#define EC_SOAP_H

#include <ec/vector.h>
#include <ec/asyncOp.h>

namespace ec {
    class Soap {
public:
        static const char ecs[4];
        static const char ias[4];
        static const char cas[4];
        static const char beginningFmt[];
        static const char ending[];
        ECAsyncOpEnv *env; //size 0x4, offset 0x0
        ECOstringstream stream; //size 0x4, offset 0x1c
        ECString response; //size 0x4, offset 0x28
        ECString unk0x34; //size 0x4, offset 0x34
        int httpStatus; //size 0x4, offset 0x40
        ECResult status; //size 0x4, offset 0x44
        long commError; //size 0x4, offset 0x48
        u8 unk0x4c; //size 0x1, offset 0x4c
        u8 unk0x4d; //size 0x1, offset 0x4d
        char *action; //size 0x4, offset 0x84
        const char *service; //size 0x4, offset 0x88
        int unk0x94; //size 0x4, offset 0x94
        ECVector<size_t> unk0x98; //size 0xc, offset 0x98
        ECVector<ECString> tagStack; //size unkown, offset 0xa4
        ECString &indent; //size 0x4, offset 0xbc, indent size?
        char *unk0xc8; //size 0x4, offset 0xc8
        size_t oneIndentLen; //size 0x4, offset 0xcc
        void addElement(const char *, const char *);
        void startComplex(const char *); 
        void end();
        void endComplex();
        ECResult getResp(const ECString &);
        ECResult getWsResponse(const ECString &);
        void getCommonElements();
    };
}

#endif