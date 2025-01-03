#include "midi/DisplayEvents.h"
#include "rndobj/Rnd.h"

// retail scratch: https://decomp.me/scratch/s0VoZ
float DisplayEvents(DataEventList* events, float f1, float f2){
    float f9 = f1 + 2.0f;
    int min = Min(events->mCurIndex, events->Size() - 1);
    MaxEq(min, 0);
    while(min > 0 && events->Event(min - 1).end > f2) min--;
    while(min < events->Size() && events->Event(min).end < f2) min++;
    float f10 = -1.0f;
    while(min < events->Size() && events->Event(min).start < f2 + (float)TheRnd->Width() / 200.0f){
        DataEvent curEvent(events->Event(min));
        float start14c = (curEvent.start - f2) * 200.0f + 5.0f;
        float start150 = (curEvent.end - f2) * 200.0f + 5.0f;
        String str108;
        str108 << curEvent.Msg();
        MaxEq(start14c, 5.0f);
        MinEq(start150, (float)TheRnd->Width() + 5.0f);
        if(min < events->Size() - 1){
            MinEq(start150, ((events->Event(min + 1).start - f2) * 200.0f + 5.0f) - 1.0f);
        }
        TheRnd->DrawRect(Hmx::Rect(start14c, f1 + 2.0f, Max(1.0f, start150-start14c), 12.0f), Hmx::Color(0,0,1), 0, 0, 0);
        if(f10 == -1.0f){
            f10 = Max(f10, 
                TheRnd->DrawString(MakeString("%.2f: %s", curEvent.start, str108.c_str()), Vector2(start14c, f9 + 14.0f), Hmx::Color(1,1,1), true).y);
        }
        min++;
    }
    TheRnd->DrawRect(Hmx::Rect(5.0f, f9 - 2.0f, 1.0f, 14.0f), Hmx::Color(1,0,0), 0, 0, 0);
    return f9 + f10;
}