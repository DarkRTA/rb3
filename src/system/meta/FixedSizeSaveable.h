#ifndef META_FIXEDSIZESAVEABLE_H
#define META_FIXEDSIZESAVEABLE_H
#include "utl/BinStream.h"
#include "utl/BufStream.h"
#include "meta/FixedSizeSaveableStream.h"
#include "os/Debug.h"
#include "utl/STLHelpers.h"
#include <set>

typedef int SaveSizeMethodFunc(int);

class FixedSizeSaveable {
public:
    FixedSizeSaveable();
    virtual ~FixedSizeSaveable();
    virtual void SaveFixed(FixedSizeSaveableStream&) const = 0;
    virtual void LoadFixed(FixedSizeSaveableStream&, int) = 0;

    static void Init(int, int);
    static void PadStream(FixedSizeSaveableStream&, int);
    static void DepadStream(FixedSizeSaveableStream&, int);
    static void SaveFixedSymbol(FixedSizeSaveableStream&, const Symbol&);
    static void LoadFixedSymbol(FixedSizeSaveableStream&, Symbol&);
    static void SaveFixedString(FixedSizeSaveableStream&, const class String&);
    static void LoadFixedString(FixedSizeSaveableStream&, class String&);
    static void SaveSymbolID(FixedSizeSaveableStream&, Symbol);
    static void LoadSymbolFromID(FixedSizeSaveableStream&, Symbol&);
    static void SaveSymbolTable(FixedSizeSaveableStream&, int, int);
    static void LoadSymbolTable(FixedSizeSaveableStream&, int, int);
    static void SaveStd(FixedSizeSaveableStream&, const std::vector<Symbol>&, int);
    static void LoadStd(FixedSizeSaveableStream&, std::vector<Symbol>&, int);
    static void SaveStd(FixedSizeSaveableStream&, const std::list<Symbol>&, int);
    static void LoadStd(FixedSizeSaveableStream&, std::list<Symbol>&, int);
    static void SaveStd(FixedSizeSaveableStream&, const std::set<Symbol>&, int);
    static void LoadStd(FixedSizeSaveableStream&, std::set<Symbol>&, int);
    static void EnablePrintouts(bool);

    // Note: `Allocator` here is actually the size/capacity type parameter on Wii.
    // The name is based on Xbox 360 symbols, which show the allocator type instead.
    template <class T, class Allocator>
    static void SaveStdFixed(FixedSizeSaveableStream& stream, const std::vector<T, Allocator>& vec, int maxsize){
        int savesize = T::SaveSize(FixedSizeSaveable::sSaveVersion);
        int vecsize = vec.size();
        if(vecsize > maxsize){
            MILO_WARN("The vector size is greater than the maximum supplied! size=%i max=%i\n", vecsize, maxsize);
            vecsize = maxsize;
        }
        stream << vecsize;
        for(int i = 0; i < vecsize; i++){
            vec[i].SaveFixed(stream);
        }
        if(maxsize > vecsize) PadStream(stream, savesize * (maxsize - vecsize));
    }

    template <class T, class Allocator>
    static void LoadStdFixed(FixedSizeSaveableStream& stream, std::vector<T, Allocator>& vec, int maxsize, int i2){
        int savesize = T::SaveSize(i2);
        if(vec.size() != 0){
            MILO_WARN("vector is not empty!");
            vec.clear();
        }
        int vecsize;
        stream >> vecsize;
        vec.resize(vecsize);
        for(int i = 0; i < vecsize; i++){
            vec[i].LoadFixed(stream, i2);
        }
        if(maxsize > vecsize) DepadStream(stream, savesize * (maxsize - vecsize));
    }

    template <class T, class Allocator>
    static void SaveStd(FixedSizeSaveableStream& stream, const std::vector<T, Allocator>& vec, int maxsize, int savesize){
        int vecsize = vec.size();
        if(vecsize > maxsize){
            MILO_WARN("The vector size is greater than the maximum supplied! size=%i max=%i\n", vecsize, maxsize);
            vecsize = maxsize;
        }
        stream << vecsize;
        for(int i = 0; i < vecsize; i++){
            stream << vec[i];
        }
        if(maxsize > vecsize) PadStream(stream, (savesize * (maxsize - vecsize)));
    }

    template <class T, class Allocator>
    static void LoadStd(FixedSizeSaveableStream& stream, std::vector<T, Allocator>& vec, int maxsize, int savesize){
        if(vec.size() != 0){
            MILO_WARN("vector is not empty!");
            vec.clear();
        }
        int vecsize;
        stream >> vecsize;
        vec.resize(vecsize);
        for(int i = 0; i < vecsize; i++){
            stream >> vec[i];
        }
        if(maxsize > vecsize) DepadStream(stream, savesize * (maxsize - vecsize));
    }

    template <class T>
    static void SaveStd(FixedSizeSaveableStream& stream, const std::map<Symbol, T>& map, int maxsize, int savesize){
        int mapsize = map.size();
        if(mapsize > maxsize){
            MILO_WARN("The hash_map size is greater than the maximum supplied! size=%i max=%i\n", mapsize, maxsize);
            mapsize = maxsize;
        }
        stream << mapsize;
        for(std::map<Symbol, T>::const_iterator it = map.begin(); it != map.end(); ++it){
            FixedSizeSaveable::SaveSymbolID(stream, it->first);
            stream << it->second;
        }
        if(maxsize > mapsize) PadStream(stream, savesize * (maxsize - mapsize));
    }

    template <class T1, class T2>
    static void SaveStd(FixedSizeSaveableStream& stream, const std::map<T1, T2>& map, int maxsize, int savesize){
        int mapsize = map.size();
        if(mapsize > maxsize){
            MILO_WARN("The hash_map size is greater than the maximum supplied! size=%i max=%i\n", mapsize, maxsize);
            mapsize = maxsize;
        }
        stream << mapsize;
        for(std::map<T1, T2>::const_iterator it = map.begin(); it != map.end(); ++it){
            stream << it->first;
            stream << it->second;
        }
        if(maxsize > mapsize) PadStream(stream, savesize * (maxsize - mapsize));
    }

    template <class T, class Allocator>
    static void SaveStdPtr(FixedSizeSaveableStream& stream, const std::list<T*, Allocator>& list, int maxsize, int savesize){
        int lsize = list.size();
        if(lsize > maxsize){
            MILO_WARN("The list size is greater than the maximum supplied! size=%i max=%i\n", lsize, maxsize);
            lsize = maxsize;
        }
        stream << lsize;
        for(std::list<T*, Allocator>::const_iterator it = list.begin(); it != list.end(); ++it){
            stream << *(*it);
        }
        if(maxsize > lsize) PadStream(stream, (savesize * (maxsize - lsize)));
    }

    template <class T>
    static void LoadStd(FixedSizeSaveableStream& stream, std::map<Symbol, T>& map, int maxsize, int savesize){
        if(map.size() != 0){
            MILO_WARN("hash_map is not empty!");
            map.clear();
        }
        int mapsize;
        stream >> mapsize;
        for(int i = 0; i < mapsize; i++){
            Symbol key;
            FixedSizeSaveable::LoadSymbolFromID(stream, key);
            T value;
            stream >> value;
            map[key] = value;
        }
        if(maxsize > mapsize) DepadStream(stream, savesize * (maxsize - mapsize));
    }

    template <class T1, class T2>
    static void LoadStd(FixedSizeSaveableStream& stream, std::map<T1, T2>& map, int maxsize, int savesize){
        if(map.size() != 0){
            MILO_WARN("hash_map is not empty!");
            map.clear();
        }
        int mapsize;
        stream >> mapsize;
        for(int i = 0; i < mapsize; i++){
            T1 key;
            stream >> key;
            T2 value;
            stream >> value;
            map[key] = value;
        }
        if(maxsize > mapsize) DepadStream(stream, savesize * (maxsize - mapsize));
    }

    template <class T, class Allocator>
    static void LoadStdPtr(FixedSizeSaveableStream& stream, std::list<T*, Allocator>& list, int maxsize, int savesize){
        if(list.size() != 0){
            MILO_WARN("list is not empty!");
            DeleteAll(list);
        }
        int lsize;
        stream >> lsize;
        for(int i = 0; i < lsize; i++){
            T* itemptr = new T();
            stream >> *itemptr;
            list.push_back(itemptr);
        }
        if(maxsize > lsize) DepadStream(stream, (savesize * (maxsize - lsize)));
    }

    static int GetMaxSymbols(){
        MILO_ASSERT(sMaxSymbols >= 0, 0x1C0);
        return sMaxSymbols;
    }

    static int sCurrentMemcardLoadVer;
    static int sSaveVersion;
    static int sMaxSymbols;
    static bool sPrintoutsEnabled;
    SaveSizeMethodFunc* mSaveSizeMethod;

    static int GetSaveVersion(){ return sSaveVersion; }
};

FixedSizeSaveableStream& operator<<(FixedSizeSaveableStream&, const FixedSizeSaveable&);
FixedSizeSaveableStream& operator>>(FixedSizeSaveableStream&, FixedSizeSaveable&);

#define REPORT_SIZE(name, size) \
    if(FixedSizeSaveable::sPrintoutsEnabled){ \
        MILO_LOG("* %s = %i\n", name, size); \
    } \
    return size;

#endif
