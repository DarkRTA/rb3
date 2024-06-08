#ifndef BANDTRACK_GEM_H
#define BANDTRACK_GEM_H

#include "bandtrack/Tail.h"
#include "beatmatch/GameGem.h"
#include "track/TrackWidget.h"
#include "types.h"
#include <functional>

class Gem {
    public:
    Gem(const GameGem&, unsigned int, float, float, bool, int, int, bool);
    ~Gem();
    Gem& operator=(const Gem&);
    bool OnScreen(float);
    void Poll(float, float, float, float, float);
    // void AddRep(GemRepTemplate&, RndGroup*, Symbol, const TrackConfig&, bool);
    bool UseRGChordStyle() const;
    void RemoveRep();
    void AddInstance(Symbol, int);
    void AddChordInstance(Symbol);
    void AddStrumInstance(Symbol, Symbol);
    void AddWidgetInstanceImpl(TrackWidget*, int);
    void AddHopoTails(Symbol);
    void RemoveAllInstances();
    void SetType(Symbol);
    void UpdateTailPositions();
    void CreateWidgetInstances(Symbol);
    void Miss();
    void Hit();
    void PartialHit(unsigned int);
    void Release();
    void ApplyDuration(float, float, float);
    void ReleaseSlot(int);
    void KillDuration();
    void Reset();
    float GetStart() const;
    void InitChordInfo(int, bool);
    void SetFretPos(int);
    void GetChordFretLabelInfo(String&, int&) const;

    int unk_0x0;
    const GameGem* unk_0x4;
    std::set<TrackWidget*> unk_0x8;
    float unk_0x20, unk_0x24, unk_0x28;
    int unk_0x2C;
    std::vector<Tail*> unk_0x30;
    int unk_0x38;
    float unk_0x3C, unk_0x40;
    int unk_0x44, unk_0x48;
    class String unk_0x4C;
    u8 unk_0x58;
    int unk_0x5C, unk_0x60;
    u8 unk_0x64, unk_0x65;
    bool unk_0x66_0 : 1, unk_0x66_1 : 1, unk_0x66_2 : 1, unk_0x66_3 : 1, unk_0x66_4 : 1, unk_0x66_5 : 1, unk_0x66_6 : 1;
    bool unk_0x67;
};

#endif // BANDTRACK_GEM_H
