#include "Cam.h"

Transform WiiCam::sViewToWiiViewXfm;
Transform WiiCam::sWiiViewToViewXfm;

WiiCam::WiiCam() {}

void WiiCam::Select() {

}

u32 WiiCam::ProjectZ(float f1) {
    float f3 = mNearPlane - mFarPlane;
    float f2 = mZRange.y - mZRange.x;
    float f5 = mFarPlane / f3;
    float f3_2 = mNearPlane * mFarPlane;
    f3_2 = f1 * f5 - f3_2;
    f1 = f3_2 / f1;
    f1 = f1 * f2 + mZRange.x;
    return 16777215 * f1;
}
