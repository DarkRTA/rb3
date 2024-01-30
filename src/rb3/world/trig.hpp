#ifndef RB3_TRIG_HPP
#define RB3_TRIG_HPP

void TrigTableInit(); // fn_802E2E28
void TrigTableTerminate();
float Lookup(float); // fn_802E2F90
float Sine(float); // fn_802E2F38
float FastSin(float); // fn_802E2FE8
float Cosine(float); // fn_802DE4D4

#endif
