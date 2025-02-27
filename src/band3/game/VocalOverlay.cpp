#include "game/VocalOverlay.h"
#include "VocalScoreHistory.h"
#include "decomp.h"
#include "game/VocalPart.h"
#include "game/Singer.h"
#include "os/Debug.h"
#include "synth/MicManagerInterface.h"

MicClientID sNullMicClientID;

VocalOverlay::VocalOverlay() : unk20(0), unk24(0) {}

VocalOverlay::~VocalOverlay() {}

void VocalOverlay::Reset(int n) {
    mSingerStrings.resize(n);
    for (int i = 0; i < n; i++) {
        mSingerStrings[i] = MakeString("Singer %i ", i + 1);
    }
    mFooterString.erase();
}

void VocalOverlay::AppendSingerPitch(int i1, float f2) {
    if (f2 != 0) {
        mSingerStrings[i1] += MakeString("%4.1f > ", f2);
    } else {
        mSingerStrings[i1] += " -.-!> ";
    }
}

void VocalOverlay::AddPossiblePart(int i1, VocalPart *part) {
    if (part) {
        mSingerStrings[i1] += MakeString("@%d ", part->PartIndex() + 1);
    } else {
        mSingerStrings[i1] += "   ";
    }
}

DECOMP_FORCEACTIVE(VocalOverlay, "%d:%5.1f ")

void VocalOverlay::EqualizeSingerStrings() {
    for (int i = 0; i < mSingerStrings.size(); i++) {
        String &cur = mSingerStrings[i];
        if (cur.length() < 25) {
            mSingerStrings[i] += String(25 - cur.length(), ' ');
        }
    }
}

void VocalOverlay::AppendAssignedPart(
    const Singer *iSinger, const std::vector<VocalPart *> &parts
) {
    MILO_ASSERT(iSinger, 0x73);
    int i4 = iSinger->GetFrameAssignedPart();
    int i5 = iSinger->GetSingerIndex();
    if (i4 != -1) {
        mSingerStrings[i5] += MakeString(" $%d ", i4 + 1);
        const VocalScoreCache &cache = iSinger->AccessScoreCache(parts[i4]->PartIndex());
        mSingerStrings[i5] += MakeString(" %3.1f%% ", cache.unk0);
    } else {
        mSingerStrings[i5] += MakeString("    ");
        mSingerStrings[i5] += MakeString("      ");
    }
}

DECOMP_FORCEACTIVE(VocalOverlay, "  (o%+2d / %4.1f )")

void VocalOverlay::AppendEnergy(int i1, float f2, float f3) {
    if (f2 > unk20 || f3 > unk24 + 1000.0f) {
        unk20 = f2;
        unk24 = f3;
    }
    mSingerStrings[i1] += MakeString("  E %0.3f (%0.3f)", f2, unk20);
}

void VocalOverlay::AppendTalkyData(int i1, bool b2, bool b3, float f4) {
    mSingerStrings[i1] += MakeString("  %s %0.5f", b2 ? "VOX" : "---", f4);
}

void VocalOverlay::AppendDeploymentTime(int i1, float f2) {
    mSingerStrings[i1] += MakeString(" D%4.0f", f2);
}

void VocalOverlay::AppendDeploymentMarker(int i1) {
    if (i1 != -1)
        mSingerStrings[i1] += " <<";
}

void VocalOverlay::AppendPartData(const std::vector<VocalPart *> &parts) {
    int i6 = 0;
    FOREACH (it, parts) {
        const VocalPart *cur = *it;
        char c = '?';
        switch (cur->unk98) {
        case 0:
            c = 'p';
            break;
        case 1:
            c = 't';
            break;
        case 2:
            c = '*';
            break;
        case 3:
            c = 'D';
            break;
        }
        if (it != parts.begin())
            mFooterString += "  ||  ";
        mFooterString +=
            MakeString("p%i: %c %4i pts", cur->PartIndex() + 1, c, (int)cur->unk20);
        i6 += (int)cur->unk20;
    }
    mFooterString += MakeString("    total pts: %4i", i6);
}

void VocalOverlay::AppendPhraseMeter(float f1) {
    mFooterString += MakeString("  %% %4.2f", f1);
}

void VocalOverlay::FinalizeDisplayString() {
    mDisplayedString.erase();
    FOREACH (it, mSingerStrings) {
        mDisplayedString += String("\n") + *it;
    }
    mDisplayedString += String("\n") + mFooterString;
}