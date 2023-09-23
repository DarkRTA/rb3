#include <types.h>

class String {
public:
    String();
    String(char * src);
    String(String * src);
    ~String();
    operator_=(char * src);
};
