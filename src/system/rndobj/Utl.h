#ifndef RNDOBJ_UTL_H
#define RNDOBJ_UTL_H

#include "rndobj/Group.h"
#include "rndobj/Mesh.h"

RndGroup* GroupOwner(Hmx::Object*);
float ConvertFov(float a, float b);
void SetLocalScale(RndTransformable*, const Vector3&);
void AttachMesh(RndMesh*, RndMesh*);
void UtilDrawSphere(const Vector3&, float, const Hmx::Color&);
void UtilDrawAxes(const Transform&, float, const Hmx::Color&);
void TransformKeys(class RndTransAnim*, const Transform&);

void RndUtlPreInit();
void RndUtlInit();
void RndUtlTerminate();

#endif // RNDOBJ_UTL_H
