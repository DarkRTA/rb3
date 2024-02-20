#ifndef META_MEMCARDACTION_H
#define META_MEMCARDACTION_H

class Profile;

class MemcardAction {

    MemcardAction(Profile*);
    virtual ~MemcardAction() {}
    virtual void PreAction() = 0;
    virtual void Action() = 0;
    virtual void PostAction() = 0;

    int unk_04;
    char* mBuf;
    int mBufLen;
    Profile* unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;


    void SetBuffer(char*, int);
};

#endif // META_MEMCARDACTION_H
