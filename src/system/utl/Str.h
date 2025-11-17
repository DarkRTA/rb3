#ifndef UTL_STR_H
#define UTL_STR_H
#include "utl/TextStream.h"
#include "utl/Symbol.h"
#include <string.h>
#include <vector>

// i can't think of a better place to put this
inline bool IsAsciiNum(char c) { return c >= 0x30 && c <= 0x39; }

// ditto
inline bool streq(const char *s1, const char *s2) { return strcmp(s1, s2) == 0; }

inline bool strneq(const char *s1, const char *s2, int n) {
    return strncmp(s1, s2, n) == 0;
}

inline bool strieq(const char *s1, const char *s2) { return stricmp(s1, s2) == 0; }

class String : public TextStream {
public:
    unsigned int mCap;
    char *mStr;

    virtual ~String();
    virtual void Print(const char *);

    String();
    String(const char *);
    String(Symbol);
    String(const String &);
    String(unsigned int, char);

    static const unsigned int npos;

    unsigned int length() const { return strlen(mStr); }
    unsigned int capacity() const { return mCap; }
    const char *c_str() const { return mStr; }
    bool empty() const { return *mStr == '\0'; }

    void reserve(unsigned int);

    String operator+(const char *) const;
    String operator+(char) const;
    String operator+(const String &) const;
    String &operator+=(const char *);
    String &operator+=(Symbol);
    String &operator+=(const String &);
    String &operator+=(char);
    String &operator=(const char *);
    String &operator=(Symbol);
    String &operator=(const String &);

    char &operator[](unsigned int);
    char rindex(int) const;
    char &rindex(int);

    bool operator!=(const char *) const;
    bool operator!=(const String &) const;
    bool operator==(const char *) const;
    bool operator==(const String &) const;
    bool operator<(const String &) const;

    void resize(unsigned int);
    unsigned int find(char, unsigned int) const;
    unsigned int find(char) const;
    unsigned int find(const char *) const;
    unsigned int find(const char *, unsigned int) const;
    unsigned int find_first_of(const char *, unsigned int) const;
    unsigned int find_last_of(char) const;
    unsigned int find_last_of(const char *) const;
    unsigned int rfind(const char *) const;

    bool contains(const char *) const;

    int split(const char *token, std::vector<String> &subStrings) const;

    String substr(unsigned int) const;
    String substr(unsigned int, unsigned int) const;

    void ToLower();
    void ToUpper();

    void ReplaceAll(char, char);
    void swap(String &);
    String &replace(unsigned int, unsigned int, const char *);
    String &erase();
    String &erase(unsigned int);
    String &erase(unsigned int, unsigned int);
    String &insert(unsigned int, unsigned int, char);
    String &insert(unsigned int, const char *);
    String &insert(unsigned int, const String &);

    operator const char *() const { return c_str(); }
};

bool SearchReplace(const char *, const char *, const char *, char *);
bool StrNCopy(char *, const char *, int);

inline TextStream &operator<<(TextStream &ts, const String &str) {
    ts.Print(str.c_str());
    return ts;
}

#endif
