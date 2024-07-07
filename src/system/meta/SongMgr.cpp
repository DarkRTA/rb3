#include "SongMgr.h"

int GetSongID(DataArray*, DataArray*){

}

int CountSongsInArray(DataArray* arr){
    int i = 0;
    int size = arr->Size();
    for(; i < size && arr->Node(i).Type() != kDataArray; i++);
    return size - i;
}

SongMgr::~SongMgr() {}
void SongMgr::Init() {}
bool SongMgr::HasSong(int) const { return false; }
bool SongMgr::HasSong(Symbol, bool) const { return false; }
SongMetadata* SongMgr::Data(int) const { return 0; }
void SongMgr::ContentStarted() {}
bool SongMgr::ContentDiscovered(Symbol) {}
void SongMgr::ContentDone() {}
void SongMgr::ContentMounted(const char*, const char*) {}
void SongMgr::ContentUnmounted(const char*) {}

const char* SongMgr::ContentName(int i) const {
    char buf[128];
    SongMetadata* metadata = Data(i);
    if(metadata){
        if(metadata->IsOnDisc()) return 0;
        else {
            const char* filename = metadata->SongBlock()->GetBaseFileName();
            strcpy(buf, filename+4);
            char* str1 = strchr(buf, '/');
            if(str1 != 0){
                char* str2 = strchr(str1 + 1, '/');
                if(str2 != 0) *str2 = '\0';
            }
            return MakeString("%s", buf);
        }
    }
    else return 0;
}

void SongMgr::SongAudioData(Symbol) const {

}

const char* SongMgr::ContentName(Symbol, bool) const {}
void SongMgr::GetContentNames(Symbol, std::vector<Symbol>&) const {}
bool SongMgr::SongCacheNeedsWrite() const {}
void SongMgr::IsSongCacheWriteDone() const {}
void SongMgr::IsSongMounted(Symbol) const {}