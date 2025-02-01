#pragma once
#include "synth/FxSend.h"

/** "A reverb effect." */
class FxSendReverb : public FxSend {
public:
    FxSendReverb();
    virtual ~FxSendReverb();
    OBJ_CLASSNAME(FxSendReverb);
    OBJ_SET_TYPE(FxSendReverb);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(FxSendReverb);
    static void Init() { REGISTER_OBJ_FACTORY(FxSendReverb) }

    /** "The reverb environment to simulate.". Possible options:
     *  (default generic padded_cell room bath_room living_room stone_room auditorium
     * concert_hall cave arena hangar carpeted_hallway hallway stone_corridor alley forest
     * city mountains quarry plain parking_lot sewer_pipe underwater small_room
     * medium_room large_room medium_hall large_hall plate)
     */
    Symbol mEnvironmentPreset; // 0x48
    // everything below this line is a PS3 param
    /** "Pre-delay in milliseconds". Ranges from 0 to 148. */
    float mPreDelayMs; // 0x4c
    /** "High cutoff frequency in Hz". Ranges from 0 to 20000. */
    float mHighCut; // 0x50
    /** "Low cutoff frequency in Hz". Ranges from 0 to 20000. */
    float mLowCut; // 0x54
    /** "Room size (0-1)" */
    float mRoomSize; // 0x58
    /** "Amount of damping (0-1)" */
    float mDamping; // 0x5c
    /** "Amount of dffusion (0-1)" */
    float mDiffusion; // 0x60
    /** "Balance of early and late reflections; 0=early only, 1=late only" */
    float mEarlyLate; // 0x64
};
