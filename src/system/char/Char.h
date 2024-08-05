#ifndef CHAR_CHAR_H
#define CHAR_CHAR_H
#include "char/Character.h"
#include "char/CharBoneDir.h"
#include "char/CharBoneOffset.h"
#include "char/CharBones.h"

#include "obj/Object.h"
void CharDeferHighlight(Hmx::Object*);
void CharInit(), CharTerminate();

extern float gCharHighlightY;

#endif