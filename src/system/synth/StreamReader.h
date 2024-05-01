#ifndef SYNTH_STREAMREADER_H
#define SYNTH_STREAMREADER_H

class StreamReader {
public:
    StreamReader(){}
    virtual ~StreamReader(){}
    virtual void Poll(float) = 0;
    virtual void Seek(int) = 0;
    virtual void EnableReads(bool) = 0;
    virtual bool Done() = 0;
    virtual bool Fail() = 0;
    virtual void Init() = 0;
};

#endif
