#include "Band.h"
#include "bandobj/BandButton.h"
#include "bandobj/BandCamShot.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandCharacter.h"
#include "bandobj/BandConfiguration.h"
#include "bandobj/BandCrowdMeter.h"
#include "bandobj/BandDirector.h"
#include "bandobj/BandFaceDeform.h"
#include "bandobj/BandHeadShaper.h"
#include "bandobj/BandHighlight.h"
#include "bandobj/BandIKEffector.h"
#include "bandobj/BandLeadMeter.h"
#include "bandobj/BandList.h"
#include "bandobj/BandRetargetVignette.h"
#include "bandobj/BandScoreboard.h"
#include "bandobj/BandSong.h"
#include "bandobj/BandSongPref.h"
#include "bandobj/BandStarDisplay.h"
#include "bandobj/BandSwatch.h"
#include "bandobj/BandWardrobe.h"
#include "bandobj/CharKeyHandMidi.h"
#include "bandobj/CheckboxDisplay.h"
#include "bandobj/ChordShapeGenerator.h"
#include "bandobj/CrowdAudio.h"
#include "bandobj/CrowdMeterIcon.h"
#include "bandobj/DialogDisplay.h"
#include "bandobj/EndingBonus.h"
#include "bandobj/GemTrackDir.h"
#include "bandobj/InlineHelp.h"
#include "bandobj/InstrumentDifficultyDisplay.h"
#include "bandobj/LayerDir.h"
#include "bandobj/MeterDisplay.h"
#include "bandobj/MicInputArrow.h"
#include "bandobj/MiniLeaderboardDisplay.h"
#include "bandobj/OutfitConfig.h"
#include "bandobj/OverdriveMeter.h"
#include "bandobj/OvershellDir.h"
#include "bandobj/PatchRenderer.h"
#include "bandobj/PitchArrow.h"
#include "bandobj/PlayerDiffIcon.h"
#include "bandobj/ReviewDisplay.h"
#include "bandobj/ScoreDisplay.h"
#include "bandobj/ScrollbarDisplay.h"
#include "bandobj/SongSectionController.h"
#include "bandobj/StarDisplay.h"
#include "bandobj/StreakMeter.h"
#include "bandobj/TrackPanelDir.h"
#include "bandobj/UnisonIcon.h"
#include "bandobj/VocalTrackDir.h"
#include "decomp.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "obj/DataUtl.h"
#include "obj/Dir.h"
#include "ui/UILabel.h"
#include "world/ColorPalette.h"

DataNode OnPaletteSync(DataArray* array) {
    ColorPalette* colpal = array->Obj<ColorPalette>(1);
    for (std::vector<ObjRef*>::reverse_iterator rit = colpal->mRefs.rbegin(); rit != colpal->mRefs.rend(); rit++) {
        Hmx::Object* refowner = (*rit)->RefOwner();
        OutfitConfig* outcfg = dynamic_cast<OutfitConfig*>(refowner);
        if (outcfg) {
            outcfg->Recompose();
        }
        BandSwatch* swatch = dynamic_cast<BandSwatch*>(refowner);
        if (swatch) {
            swatch->SetColors(colpal);
        }
    }
    return 0;
}

void BandInit() {
    if (DataGetMacro("INIT_BAND")) {
        BandButton::Init();
        BandCamShot::Init();
        BandConfiguration::Init();
        BandCrowdMeter::Init();
        BandHighlight::Init();
        BandIKEffector::Init();
        BandRetargetVignette::Init();
        BandLabel::Init();
        BandLeadMeter::Init();
        BandList::Init();
        BandScoreboard::Init();
        BandStarDisplay::Init();
        BandCharacter::Init();
        BandCharDesc::Init();
        OutfitConfig::Init();
        BandDirector::Init();
        BandFaceDeform::Init();
        BandSong::Init();
        BandWardrobe::Init();
        DialogDisplay::Init();
        BandSwatch::Init();
        CrowdMeterIcon::Init();
        EndingBonus::Init();
        GemTrackDir::Init();
        LayerDir::Init();
        PatchRenderer::Init();
        PitchArrow::Init();
        PlayerDiffIcon::Init();
        InstrumentDifficultyDisplay::Init();
        ScrollbarDisplay::Init();
        CheckboxDisplay::Init();
        ScoreDisplay::Init();
        ReviewDisplay::Init();
        StarDisplay::Init();
        MeterDisplay::Init();
        MiniLeaderboardDisplay::Init();
        MicInputArrow::Init();
        InlineHelp::Init();
        StreakMeter::Init();
        OverdriveMeter::Init();
        TrackPanelDir::Init();
        VocalTrackDir::Init();
        ChordShapeGenerator::Init();
        UnisonIcon::Init();
        OvershellDir::Init();
        CharKeyHandMidi::Init();
        SongSectionController::Init();
        BandSongPref::Init();
        BandHeadShaper::Init();
        CrowdAudio::Init();

        TheDebug.AddExitCallback(BandTerminate);
        static DataNode& mode = DataVariable("band.play_mode");
        mode = DataNode(kDataSymbol, Symbol("coop_bg").Str());
        DataRegisterFunc("palette_sync", OnPaletteSync);
        PreloadSharedSubdirs("band");
    }
}

void BandTerminate() {
    if (DataGetMacro("INIT_BAND")) {
        UILabel::Terminate();
        BandHeadShaper::Terminate();
        PatchRenderer::Terminate();
        BandSwatch::Terminate();
        OutfitConfig::Terminate();
        BandDirector::Terminate();
        BandCharacter::Terminate();
    }
}
