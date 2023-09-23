#include <rb3/String.hpp>

void String::fn_80361F88(String * src) // clone?
{
    char *pcSrc;
    pcSrc = fn_8000DB9C(src);
    fn_80361F04(this,pcSrc);
    return;
}

void String::operator_= (char * str) {
    if (str == this->text) {
        return this;
    }

    if ((str == (char *)0) || (*str == '\0')) {
        fn_80362260(this, 0);
    } else {
        fn_80361C90(this, strlen(str));
        strcpy(this->text, str);
    }

    return this;
}
