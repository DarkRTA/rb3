#include <rb3/String.hpp>
void operator_= (char * str) {
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
