/*
    VF is an external library, so I'm putting all the headers here for now
    The GC/Wii decomp guys called it "CBT" so I'm leaving it at that
    https://github.com/SMGCommunity/Petari/blob/master/libs/RVL_SDK/docs/lib/vf.md
*/

#ifndef UTL_VF_H
#define UTL_VF_H

int VFIsAvailable();
void VFInitEx();
bool VFMountDriveNANDFlashEx(const char*, const char*);
int VFUnmountDrive(const char*);
void* VFOpenFile(const char*, const char*, unsigned int);
int VFCloseFile(void*); 	
int VFSeekFile(void*, signed int, signed int); 	
int VFReadFile(void*, void*, unsigned int, unsigned int*);
int VFFileSync(void*); 	
int VFWriteFile(void*, const void*, unsigned int); 	
int VFDeleteFile(const char*); 	
int VFGetFileSizeByFd(void*); 	
int VFGetLastError(); 	
int VFGetLastDeviceError(const char*); 	
int VFGetDriveFreeSize(const char*); 	
int VFSetSyncMode(const char*, unsigned int); 	


int VFCreateDir(const char*);
int VFChangeDir(const char*);
void* VFCreateFile(const char*, int);
const char* VFGetApiErrorString();

#endif // UTL_VF_H