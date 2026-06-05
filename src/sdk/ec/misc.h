#ifndef EC_MISC_H
#define EC_MISC_H
#include <ec/string.h>
#include <RVL_SDK/revolution/esp/esp.h>

namespace ec {
    typedef struct {
        int unk0x0; //size 0x4, offset 0x0
        unsigned short unk0x4; //size 0x4, offset 0x4
    } ECCmdView;
    class ECNamValStr : ECString {
private:
        ECString m_Name;
        ECString m_Value;
public:
        ECNamValStr(const char *name, const char *value) : m_Name(name), m_Value(value) {}
        ECString name();
        ECString value();
    };

    ECResult titleChannel(unsigned long long);
    unsigned int isSubscription(unsigned long long);
    ECResult getTmdSize(void *, unsigned long *);
    int isTicketForContent(const ESTicketView *, unsigned long, const ec::ECCmdView &);
    ECResult getTicketViews(unsigned long long, ESTicketView **, unsigned long *);
    ECResult reformatEcard(const ECString &, ECString &, ECString &, ECString &);


}

#endif