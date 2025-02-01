#pragma once
#include "obj/Msg.h"
#include "meta/StreamPlayer.h"
#include "utl/NetCacheLoader.h"

class StorePreviewMgr : public MsgSource {
public:
    StorePreviewMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~StorePreviewMgr();

    void ClearCurrentPreview();
    void PlayCurrentPreview();
    void SetCurrentPreviewFile(const String &);
    void DownloadPreviewFile(const String &);
    void AddToDownloadQueue(const String &);
    bool IsDownloadingFile(const String &);
    bool AllowPreviewDownload(const String &);
    void Poll();

    String mStrPathCur; // 0x1c
    StreamPlayer *mStreamPlayer; // 0x28
    NetCacheLoader *mNetCacheLoader; // 0x2c
    std::list<String> mDownloadQueue; // 0x30
    bool mRequestedPreview; // 0x38
    float mPreviewRequestedSeconds; // 0x3c
    bool mIsPreviewPlaying; // 0x40
};

DECLARE_MESSAGE(PreviewDownloadCompleteMsg, "preview_download_complete_msg")
PreviewDownloadCompleteMsg(bool b) : Message(Type(), b) {}
END_MESSAGE
;