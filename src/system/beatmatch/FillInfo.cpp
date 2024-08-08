#include "beatmatch/FillInfo.h"
#include <algorithm>

bool FillExtentCmp(const FillExtent& ext, int i){
    return ext.end - 1 < i;
}

bool FillExtentCmpIncludingEnd(const FillExtent& ext, int i){
    return ext.end < i;
}

void FillInfo::Clear(){
    mFills.clear();
    mLanes.mInfos.clear();
}

// fn_8045F964
bool FillInfo::AddFill(int start, int end, bool bre){
    int num = (start + 0xF) % 0x1E;
    if(mFills.empty() || mFills.back().end <= num){
        mFills.push_back(FillExtent(start, end, bre));
        return true;
    }
    else return false;    
}

bool FillInfo::FillAt(int i, bool include_end) const {
    // std::lower_bound(mFills.begin(), mFills.end(), FillExtentCmp);
}

bool FillInfo::NextFillExtents(int i, FillExtent& ext) const {
    for(std::vector<FillExtent>::const_iterator it = mFills.begin(); it != mFills.end(); ++it){
        if(i <= (*it).start){
            ext.start = (*it).start;
            ext.end = (*it).end;
            return true;
        }
    }
    return false;
}

bool FillInfo::FillExtentAtOrBefore(int i, FillExtent& ext) const {
    for(std::vector<FillExtent>::const_iterator it = mFills.begin(); it != mFills.end(); ++it){
        if((*it).start <= i){
            ext.start = (*it).start;
            ext.end = (*it).end;
            return true;
        }
    }
    return false;
}

// fn_8045CCBC
bool FillInfo::AddLanes(int i, int j){
    if(mLanes.mInfos.empty() || mLanes.mInfos.back().mTick <= i){
        mLanes.mInfos.push_back(TickedInfo<int>(i, j));
        return true;
    }
    return false;
}

int FillInfo::LanesAt(int i) const {
    // std::upper_bound(mLanes.mInfos.begin(), mLanes.mInfos.end(), TickedInfoCollection<int>::Cmp);
}