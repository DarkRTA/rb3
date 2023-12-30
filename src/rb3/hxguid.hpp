#ifndef RB3_HXGUID_HPP
#define RB3_HXGUID_HPP

class HxGuid {
public:
    HxGuid();

    void Clear();
    bool IsNull() const;
    bool operator==(const HxGuid&) const;
    bool operator<(const HxGuid&) const;

    int unk0, unk4, unk8, unkc;
};

#endif
