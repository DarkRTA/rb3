#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols.h"

class LocationCmp : public SongSortCmp {
public:
    LocationCmp(SavedSetlist::SetlistType, const char *, const char *, int, const char *);
    virtual ~LocationCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const LocationCmp *GetLocationCmp() const { return this; }
};

class SetlistSortByLocation : public SetlistSort {
public:
    SetlistSortByLocation() { mShortName = by_location; }
    virtual ~SetlistSortByLocation() {}
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual ShortcutNode *NewShortcutNode(FunctionSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(FunctionSortNode *) const;
    virtual SetlistSortNode *NewSetlistNode(SetlistRecord *) const;
    virtual FunctionSortNode *NewFunctionNode(Symbol) const;
};