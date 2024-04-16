#include "Archive.h"

ArkHash::ArkHash() {

}

Archive::Archive(const char* c, int i) : mArkName(c), i(0), b(false) {Read(i);} 

void Archive::GetFileInfo(const char*, int&, unsigned long long&, int&, int&) {
    
}