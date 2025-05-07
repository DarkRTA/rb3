#include "AsyncFileCNT.h"
#include "os/AsyncFile.h"
#include "os/Debug.h"
#include "os/ContentMgr_Wii.h"
#include "sdk/RVL_SDK/revolution/cnt/cnt.h"

AsyncFileCNT::AsyncFileCNT(const char *filename, int flags) : AsyncFile(filename, flags) {
    mTempBufferCNT = NULL;
    mReadSizeCNT = 0;
    mOpenHandles = -1;
    mReadInProgress = false;
    bool dlc = FileIsDLC(filename);
    mIsDLC = dlc;
    if (mIsDLC) {
        // breaks apart the DLC path to set mFilename to the filename and mContentName to
        // the DLC content package
        // example path: dlc/sZDE/455/content/songs/parrtyintheusa/parrtyintheusa

        // skip over the 'dlc/'
        const char *filename_skip = filename + 4;
        // find the next path after that (to select the titleid, sZDE)
        const char *path_sep = strchr(filename_skip, '/');
        if (path_sep) {
            // and the next one (to select the content index, 455)
            path_sep++;
            const char *path_sep_2 = strchr(path_sep + 1, '/');
            if (path_sep_2)
                path_sep = path_sep_2;
        } else {
            // if we can't find one, this probably nulls out the path seperator since this
            // will be a null string
            path_sep = filename_skip + strlen(filename_skip);
        }

        // mContentName should be sZDE/455
        int path_length = path_sep - filename_skip;
        strncpy(mContentName, path_sep, path_length);
        mContentName[path_length] = '\0';

        // set the correct filename (e.g. content/songs/parrtyintheusa/parrtyintheusa)
        mFilename = path_sep + path_length;
        MILO_LOG(
            "AsyncFileCNT: %s -> content name: %s, fname: %s\n",
            filename,
            mContentName,
            mFilename.c_str()
        );
        unk9 = 1;
    }
}

void AsyncFileCNT::_OpenAsync() {
    mSize = 0;
    if (!mFail) {
        MILO_LOG(
            "AsyncFileCNT: Open - Filename = %s, ContentName = %s\n",
            mFilename,
            mContentName
        );
        CNTHandle *handle;
        if (mIsDLC) {
            handle = TheWiiContentMgr.ContentHandleOf(mContentName);
        } else {
            handle = TheWiiContentMgr.GetChannelContentHandle();
        }
        if (handle == NULL) {
            mFail = true;
            return;
        }
        int cnt = CNTOpen(handle, mFilename.c_str(), &mCNTFileInfo);
        if (cnt == 0) {
            int len = CNTGetLength(&mCNTFileInfo);
            mSize = len;
            MILO_LOG("AsyncFileCNT: Opened file '%s' %i bytes...\n", mFilename, mSize);
            mOpenHandles = 1;
        } else {
            MILO_LOG("AsyncFileCNT: CNTOpen file '%s' failed.\n", mFilename.c_str());
            mFail = true;
        }
    }
}

void *ReadAsyncCNT(void *arg) {
    AsyncFileCNT *asyncFile = (AsyncFileCNT *)arg;
    int r = CNTRead(
        &asyncFile->mCNTFileInfo, asyncFile->mTempBufferCNT, asyncFile->mReadSizeCNT
    );
    asyncFile->mReadResultCNT = r;
    return NULL;
}

void AsyncFileCNT::_ReadAsync(void *buffer, int len) {
    if (mOpenHandles > -1) {
        MILO_ASSERT(!mReadInProgress, 146);
        mReadInProgress = true;
        mReadResultCNT = -1;
        mTempBufferCNT = buffer;
        mReadSizeCNT = (len + 0x1F & 0xFFFFFFE0); // align to 32-bytes
        OSCreateThread(
            &mCNTReadThread,
            ReadAsyncCNT,
            this,
            mCNTThreadReadStack + sizeof(mCNTThreadReadStack),
            sizeof(mCNTThreadReadStack),
            15,
            1
        );
        mCNTReadThread.specific[0] = (void *)"CNTReadThread";
        OSResumeThread(&mCNTReadThread);
    }
}

bool AsyncFileCNT::_ReadDone() {
    if (mReadInProgress == false) {
        return true;
    } else if (mOpenHandles <= -1 || mReadResultCNT == -1) {
        // fall through
    } else {
        if (mReadResultCNT < 0) {
            MILO_LOG("AsyncFileCNT: CNT READ FAILED %s = %d\n", mFilename, mReadResultCNT);
            mFail = true;
        } else {
            MILO_ASSERT(mReadResultCNT <= mReadSizeCNT, 191);
        }
        mReadInProgress = false;
        return true;
    }
    return false;
}

void AsyncFileCNT::_Close() {
    if (mOpenHandles > -1) {
        int r;
        do {
            r = _ReadDone();
        } while (r == 0);
        r = CNTClose(&mCNTFileInfo);
        mFail = r != 0;
    }
    mOpenHandles = -1;
}

int AsyncFileCNT::GetFileHandle(DVDFileInfo *&fileInfo) {
    fileInfo = NULL;
    return false;
}

void AsyncFileCNT::_SeekToTell() {
    int r = CNTSeek(&mCNTFileInfo, Tell(), 0);
    if (r != 0)
        mFail = true;
}

AsyncFileCNT::~AsyncFileCNT() { Terminate(); }

void AsyncFileCNT::_WriteAsync(const void *, int) {}
bool AsyncFileCNT::_OpenDone() { return true; }
bool AsyncFileCNT::_WriteDone() { return true; }
