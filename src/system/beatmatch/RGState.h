#ifndef BEATMATCH_RGSTATE_H
#define BEATMATCH_RGSTATE_H

class RGState {
public:
    RGState();
    void FretDown(int, int);
    void FretUp(int, int);
    unsigned int GetFret(int) const;
    bool operator!=(const RGState&) const;
    RGState& operator=(const RGState&);

    unsigned int mStrings[6];
};

unsigned int PackRGData(int, int);
void UnpackRGData(unsigned int, int&, int&);

#endif
