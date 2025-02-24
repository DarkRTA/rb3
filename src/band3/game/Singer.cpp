#include "game/Singer.h"
#include "dsp/VibratoDetector.h"
#include "game/Defines.h"
#include "game/GameMicManager.h"
#include "game/SongDB.h"
#include "game/VocalPlayer.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "synth/MicManagerInterface.h"
#include "synth/VoiceBeat.h"

MicClientID sNullClientID(-1, -1);

Singer::Singer(VocalPlayer *vp, int n)
    : mPlayer(vp), unk4(-1, -1), unkc(0), unk10(n), unk14(0), unk18(0), unk1c(0),
      unk20(0), unk24(0), unk2c(0), unk30(0), unk38(100.0f), unk3c(0), unk40(0), unk44(0),
      unk48(-1.0f), unk4c(0.8f), unk50(500.0f), mFrameMicPitch(0), unk60(0), unk64(0),
      unk6c(0), unk70(-1), unk74(0), mOctaveOffset(0), unk7c(0), unk80(0), unk84(0),
      unk88(0), unka0(0), unka4(0), unka8(0), mVibrato(0), unk244(0), unk248(0),
      unk24c(-1.0f), unk250(-1), unk254(0), unk258(0),
      mTambourineDetector(vp->mTambourineManager, this), unk29c(0), unk2a0(0), unk2a4(0) {
    CreateMicClientID();
    Difficulty diff = mPlayer->GetUser()->GetDifficulty();
    DataArray *cfg = SystemConfig("scoring", "vocals");
    cfg->FindArray("pitch_margin", true)->Float(diff + 1); // lol what happened to this
    unk28 = cfg->FindFloat("max_detune");
    unk4c = cfg->FindFloat("scream_energy_threshold");
    unk38 = cfg->FindFloat("tambourine_deployment_suppress_ms");
    mVibrato = new VibratoDetector(0, 100);
    mTalkyMatcher = new TalkyMatcher();
    for (int i = 0; i < 5; i++)
        mPitchHistory[i] = 0;

    if (n == 0) {
        GameMic *mic = TheGameMicManager->GetMic(unk4);
        if (mic) {
            DataNode node = DataVariable("playback_file");
            if (node.Type() == kDataString) {
                if (strlen(node.Str()) != 0) {
                    mic->SetInputFile(node.Str());
                }
            }
        }
    }
}

Singer::~Singer() {}

void Singer::PostLoad() {
    int numParts = mPlayer->NumParts();
    for (int i = 0; i < numParts; i++) {
        mScoreHistories.push_back(VocalScoreHistory(i, unk10));
    }
    mScoreCaches.resize(numParts);
    mResultsData.resize(numParts);
    MILO_ASSERT(mTalkyMatcher, 0xB6);
    mTalkyMatcher->LoadEvents(
        TheSongDB->GetSongData()->mVocalFeatureVectorTimes,
        TheSongDB->GetSongData()->mVocalFeatureVectorPeaks
    );
}