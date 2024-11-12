#include "PlayerBehavior.h"

PlayerBehavior::PlayerBehavior()
    : mCanDeployOverdrive(true), mTiltDeployBand(false), mFillsDeployBand(false),
      mRequireAllCodas(false), mCanFreestyleGems(false), mHasSolos(false),
      mStreakType("default"), mMaxMultiplier(2) {}

void PlayerBehavior::SetCanDeployOverdrive(bool b) { mCanDeployOverdrive = b; }

void PlayerBehavior::SetTiltDeploysBandEnergy(bool b) { mTiltDeployBand = b; }

void PlayerBehavior::SetFillsDeployBandEnergy(bool b) { mFillsDeployBand = b; }

void PlayerBehavior::SetRequireAllCodaLanes(bool b) { mRequireAllCodas = b; }

void PlayerBehavior::SetStreakType(Symbol symbol) { mStreakType = symbol; }

void PlayerBehavior::SetMaxMultiplier(int multiplier) { mMaxMultiplier = multiplier; }

void PlayerBehavior::SetCanFreestyleBeforeGems(bool b) { mCanFreestyleGems = b; }

void PlayerBehavior::SetHasSolos(bool b) { mHasSolos = b; }
