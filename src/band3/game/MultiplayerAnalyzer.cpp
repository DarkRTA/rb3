#include "MultiplayerAnalyzer.h"

MultiplayerAnalyzer::MultiplayerAnalyzer(SongData *songData)
    : mUnk_0x0(""), mSongData(songData), mUnk_0x10(), mUnk_0x18() {}

float MultiplayerAnalyzer::GetMaxPoints(const UserGuid &userGuid) const {
    const Data *data = GetData(userGuid);

    if (data == 0) {
        return 0;
    }

    return data->m_maxPoints;
}

float MultiplayerAnalyzer::GetMaxStreakPoints(const UserGuid &userGuid) const {
    const Data *data = GetData(userGuid);

    if (data == 0) {
        return 0;
    }

    return data->m_maxStreakPoints;
}

float MultiplayerAnalyzer::GetBonusPoints(const UserGuid &userGuid) const {
    const Data *data = GetData(userGuid);

    if (data == 0) {
        return 0.0f;
    }

    return data->unk_0x20 + data->unk_0x24;
}

const MultiplayerAnalyzer::Data *MultiplayerAnalyzer::GetData(const UserGuid &userGuid) const {
    for (int i = 0; i < mUnk_0x8.size(); i++) {
        if (mUnk_0x8[i].mGuid == userGuid) {
            return &mUnk_0x8[i];
        }
    }

    return 0;
}

MultiplayerAnalyzer::Data *MultiplayerAnalyzer::GetData(const UserGuid &userGuid) {
    for (int i = 0; i < mUnk_0x8.size(); i++) {
        if (mUnk_0x8[i].mGuid == userGuid) {
            return &mUnk_0x8[i];
        }
    }

    return 0;
}
