#ifndef RB3_FILECACHE_HPP
#define RB3_FILECACHE_HPP
#include "filepath.hpp"

class FileCache {
public:
    FileCache(int);
    void Init(); // returns void
    void Terminate(); // returns void
    void PollAll();
    void Poll();
    int GetFileAll(const char *);
    void GetFile(const char *);
    bool FileCached(const char *);
    void FindPath(const FilePath &, FilePath &);
    void StartSet(int);
    void EndSet();
    // void Add(const FilePath&, int, const FilePath&, DataArray*);
    void Clear();
    void DumpOverSize(int);
    int CurSize();
    bool DoneCaching();

    int unk0;
    bool unk4;
    int *unk8; // probably a stlpmtx_std::vector<> ?
    int unkc; // probably some other class
    int unk10;
};

#endif
