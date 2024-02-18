#include "utl/Str.h"

#include <string.h>

#include "unknown.hpp"
#include "utl/UTF8.h"

extern char lbl_80874588[]; //"*"

// fn_8037AD40
int DecodeUTF8(unsigned short &us, const char *str) {
    unsigned char c = str[0];
    if (c <= 0x7FU) {
        us = c;
        return 1;
    }
    unsigned char c1 = str[1];
    if (((unsigned char)(c + 0x40)) <= 0x1FU) {
        us = ((c - 0xc0) << 6) + c1 - 0x80;
        return 2;
    }
    unsigned char c2 = str[2];
    if (((unsigned char)(c + 0x20)) <= 0xFU) {
        int x3 = ((c - 0xe0) << 0xC);
        int x2 = ((c1 - 0x80) << 6);
        x3 += x2;
        us = x3 + c2 - 0x80;
        return 3;
    }
    us = 0x2A;
    return 1;
}

// fn_8037ADD4
int EncodeUTF8(String &s, unsigned int ui) {
    if (ui < 0x80) {
        s.resize(2);
        *s[0] = ui & 0xFF;
        *s[1] = 0;
        return 1;
    }
    if (ui <= 0x7FF) {
        s.resize(3);
        *s[0] = (ui >> 6) + 0xC0;
        *s[1] = (ui & 0x3F) + 0x80;
        *s[2] = 0;
        return 2;
    }
    if (ui <= 0xFFFF) {
        s.resize(4);
        *s[0] = (ui >> 0xC) + 0xE0;
        *s[1] = ((ui >> 6) & 0x3F) + 0x80;
        *s[2] = (ui & 0x3F) + 0x80;
        *s[3] = 0;
        return 3;
    }
    s = lbl_80874588;
    return 1;
}

// fn_8037AF40
void UTF8toASCIIs(char *dst, int arg1, const char *src, char arg3) {
    unsigned short us;
    int i = 0;
    const char *src_ = src;
    char *dst_ = dst;
    for (; *src_ != 0 && i < arg1 - 1; i++) {
        src_ += DecodeUTF8(us, src_);
        if (us < 0x100)
            *dst_++ = us;
        else
            *dst_++ = arg3;
    }
    *dst_ = 0;
}

// fn_8037AFD4
void ASCIItoUTF8(char *arg0, int arg1, const char *arg2) {
    memset(arg0, 0, arg1);
    String sp8;
    char *var_r31 = arg0;
    for (int i = 0; (char)arg2[i] != '\0'; i++) {
        int utf8 = EncodeUTF8(sp8, (unsigned char)arg2[i]);
        if (((var_r31 - arg0) + utf8) >= (unsigned int)arg1) {
            return;
        }
        for (int j = 0; j < sp8.length(); j++) {
            *var_r31++ = sp8.c_str()[j];
        }
    }
}

// fn_8037B534
int UTF8StrLen(const char *str) {
    unsigned short sp8;
    int var_r30;
    char *var_r29;

    var_r29 = (char *)str;
    var_r30 = 0;
    while (*var_r29 != 0) {
        sp8 = 0;
        var_r30++;
        var_r29 = &var_r29[DecodeUTF8(sp8, (const char *)var_r29)];
    }
    return var_r30;
}

extern "C" char *fn_8037B598(char *, unsigned short);

// fn_8037B598
char *fn_8037B598(char *arg0, unsigned short arg1) {
    unsigned short sp8;
    int temp_r3;

    while (*arg0 != 0) {
        sp8 = 0;
        temp_r3 = DecodeUTF8(sp8, (const char *)arg0);
        if (sp8 == arg1)
            return arg0;
        arg0 = &arg0[temp_r3];
    }
    return 0;
}

extern "C" void fn_8037B78C(char *, int, const char *, char *, char);

// fn_8037B78C
void fn_8037B78C(char *arg0, int arg1, const char *arg2, char *arg3, char arg4) {
    unsigned short sp8;
    int temp_r30;
    char *temp_r28 = arg0;

    while ((*arg2 != 0) && ((int)(arg0 - temp_r28) < (int)(arg1 - 3))) {
        sp8 = 0;
        temp_r30 = DecodeUTF8(sp8, arg2);
        if (fn_8037B598(arg3, sp8) != 0) {
            for (unsigned int i = 0; i < temp_r30; i++) {
                *arg0++ = *arg2++;
            }
        } else {
            *arg0++ = arg4;
            arg2 = &arg2[temp_r30];
        }
    }
    *arg0 = 0;
}

// fn_8037B850
void UTF8RemoveSpaces(char *arg0, int arg1, const char *arg2) {
    unsigned short sp8;
    char *temp_r29;
    bool temp_r5;
    unsigned int temp_r3;
    char *max = ((arg0 + arg1) - 3);
    bool var_r27;
    char temp_r0;

    var_r27 = true;
    temp_r29 = arg0;

    while ((*arg2 != 0) && (arg0 < max)) {
        sp8 = 0;
        temp_r3 = DecodeUTF8(sp8, arg2);
        temp_r5 = (sp8 == 0x20);
        if ((!temp_r5) || (!var_r27)) {
            for (unsigned int i = 0; i < temp_r3; i++) {
                *arg0++ = arg2[i];
            }
        }
        var_r27 = temp_r5;
        arg2 = &arg2[temp_r3];
    }
    if ((arg0 > temp_r29) && (arg0[-1] == ' ')) {
        arg0--;
    }
    *arg0 = 0;
}

extern "C" void fn_8037B930(unsigned short *, char *);

// fn_8037B930
void fn_8037B930(unsigned short *arg0, char *arg1) {
    unsigned short *var_r31;
    char *var_r30;

    var_r31 = arg0;
    var_r30 = arg1;
    while (*var_r30 != 0) {
        var_r30 = &var_r30[DecodeUTF8(*var_r31, var_r30)];
        var_r31++;
    }
    *var_r31 = 0;
}

extern "C" void fn_8037B990(unsigned short *, char *);

// fn_8037B990
void fn_8037B990(unsigned short *arg0, char *arg1) {
    char *var_r31 = arg1;
    while (*var_r31 != 0) {
        var_r31 = &var_r31[DecodeUTF8(*arg0, var_r31)];
        arg0++;
    }
    *arg0 = 0;
}

extern "C" int fn_8037B9F0(char *, unsigned short *);

// fn_8037B9F0
int fn_8037B9F0(char *arg0, unsigned short *arg1) {
    int ctr = 0;
    while (*arg1 != 0) {
        String sp8;
        int temp_r3 = EncodeUTF8(sp8, *arg1);
        ctr += temp_r3;
        if (arg0 != 0) {
            strncpy(arg0, sp8.c_str(), temp_r3);
            arg0 = &arg0[temp_r3];
        }
        arg1++;
    }
    *arg0 = 0;
    return ctr;
}

extern "C" void fn_8037B60C(unsigned short, char *);

// fn_8037B60C
void UTF8ToLower(unsigned short arg0, char *arg1) {
    int temp_r6;
    int var_r3;

    var_r3 = arg0;
    if (var_r3 < 0x80U) {
        if ((unsigned short)(var_r3 + 0xFFBF) <= 0x19U) {
            arg1[0] = (var_r3 + 0x20);
        } else
            arg1[0] = var_r3;
    } else if (var_r3 < 0x800U) {
        if ((unsigned short)(var_r3 + 0xFF40) <= 0x1DU) {
            var_r3 = (var_r3 + 0x20) & 0xffff;
        }
        arg1[0] = (((var_r3 >> 6) & 0x3FF) + 0xC0);
        arg1[1] = ((var_r3 % 64) + 0x80);
    } else {
        temp_r6 = (var_r3 >> 6) & 0x3FF;
        arg1[0] = (((var_r3 >> 0xCU) & 0xF) + 0xE0);
        arg1[1] = ((temp_r6 % 64) + 0x80);
        arg1[2] = ((var_r3 % 64) + 0x80);
    }
}

// fn_8037B66C
void UTF8ToUpper(unsigned short arg0, char *arg1) {
    int temp_r6;
    int var_r3;

    var_r3 = arg0;
    if (var_r3 < 0x80U) {
        if ((unsigned short)(var_r3 + 0xFF9F) <= 0x19U) {
            arg1[0] = (var_r3 - 0x20);
        } else
            arg1[0] = var_r3;
    } else if (var_r3 < 0x800U) {
        if ((unsigned short)(var_r3 + 0xFF20) <= 0x1DU) {
            var_r3 = (var_r3 - 0x20) & 0xffff;
        }
        arg1[0] = (((var_r3 >> 6) & 0x3FF) + 0xC0);
        arg1[1] = ((var_r3 % 64) + 0x80);
    } else {
        temp_r6 = (var_r3 >> 6) & 0x3FF;
        arg1[0] = (((var_r3 >> 0xCU) & 0xF) + 0xE0);
        arg1[1] = ((temp_r6 % 64) + 0x80);
        arg1[2] = ((var_r3 % 64) + 0x80);
    }
}
