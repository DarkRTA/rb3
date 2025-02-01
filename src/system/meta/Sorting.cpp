#include "meta/Sorting.h"
#include "utl/MakeString.h"
#include <string.h>
#include <ctype.h>

const char *AlphaKeySkip(const char *str, bool b) {
    const char *ptr = str;
    int len = strlen(str);

    if (b && len > 4 && (str[0] == 'T' || str[0] == 't')
        && (str[1] == 'H' || str[1] == 'h') && (str[2] == 'E' || str[2] == 'e')
        && (str[3] == ' ')) {
        ptr = ptr + 4;
    } else if (b && len > 2 && (str[0] == 'A' || str[0] == 'a') && (str[1] == ' ')) {
        ptr = ptr + 2;
    } else if (b && len > 3 && (str[0] == 'A' || str[0] == 'a')
               && (str[1] == 'N' || str[1] == 'n') && (str[2] == ' ')) {
        ptr = ptr + 3;
    }
    if (*ptr == '(')
        ptr++;
    return ptr;
}

void CalculateAlphaKey(char *c1, const char *c2, bool b) {
    strcpy(c1, AlphaKeySkip(c2, b));
}

inline bool NotASCII(char c) { return !(c & 0x80); }

int AlphaKeyStrCmp(const char *c1, const char *c2, bool b) {
    c1 = AlphaKeySkip(c1, b);
    c2 = AlphaKeySkip(c2, b);
    if (!NotASCII(*c1)) {
        if (NotASCII(*c2))
            return -1;
    } else if (!NotASCII(*c2))
        return 1;
    return stricmp(c1, c2);
}

Symbol FirstSortChar(const char *cc, bool b) {
    char buf[256];
    CalculateAlphaKey(buf, cc, b);

    if (NotASCII(buf[0])) {
        if (isalpha(buf[0])) {
            return Symbol(MakeString("%c", toupper(buf[0])));
        }
    }

    static Symbol non_alpha_sym("123");
    return non_alpha_sym;
}
