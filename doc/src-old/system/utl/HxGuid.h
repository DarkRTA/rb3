#ifndef UTL_HXGUID_H
#define UTL_HXGUID_H

class HxGuid {
public:
    HxGuid();

    void Generate();
    void Clear();
    bool IsNull() const;
    bool operator==(const HxGuid&) const;
    bool operator<(const HxGuid&) const;

    int unk0, unk4, unk8, unkc;
};

class UserGuid : public HxGuid {
public:
    UserGuid();
};

#endif
