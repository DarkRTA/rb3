#ifndef UTL_VF_H
#define UTL_VF_H

extern int VFIsAvailable();
extern void VFInitEx();
extern bool VFMountDriveNANDFlashEx(const char* drive, const char* sysFileName);
extern int VFUnmountDrive(const char* drive);
extern void* VFOpenFile(const char* path, const char* mode, unsigned int attr);
extern int VFCloseFile(void* file); 	
extern int VFSeekFile(void* file, signed int offset, signed int origin); 	
extern int VFReadFile(void* file, void* buf, unsigned int size, unsigned int* readSize);
extern int VFFileSync(void* file); 	
extern int VFWriteFile(void* file, const void* buf, unsigned int size); 	
extern int VFDeleteFile(const char* path); 	
extern int VFGetFileSizeByFd(void* file); 	
extern int VFGetFileSize(const char* path);
extern int VFGetLastError(); 	
extern int VFGetLastDeviceError(const char* drive); 	
extern int VFGetDriveFreeSize(const char* drive); 	
extern int VFSetSyncMode(const char* drive, unsigned int mode); 	

extern int VFMountDriveNANDFlash();

extern int VFCreateDir(const char*);
extern int VFChangeDir(const char*);
extern void* VFCreateFile(const char*, int);
extern const char* VFGetApiErrorString();

#endif // UTL_VF_H