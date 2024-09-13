#include "bandobj/ChordShapeGenerator.h"
#include "utl/Symbols.h"

ChordShapeGenerator::ChordShapeGenerator() : mFingerSrcMesh(this, 0), mChordSrcMesh(this, 0), mBaseXSection(this, 0), mContourXSection(this, 0), mBaseHeight(this, 0),
    mNumSlots(6), mString0(this, 0), mString1(this, 0), mString2(this, 0), mString3(this, 0), mString4(this, 0), mString5(this, 0), unkc4(0), unkc8(-1.0f), unkcc(1.0f), unkd0(0.2f) {
    mFretHeights.resize(7);
    for(int i = 0; i < 7; i++) mFretHeights[i] = 1.0f;
    mGradeDistances.resize(7);
    for(int i = 0; i < 7; i++) mGradeDistances[i] = 0.33f;
    mStringFrets.resize(6);
    for(int i = 0; i < 6; i++) mStringFrets[i] = -1;
    unk64.resize(6);
    for(int i = 0; i < 6; i++) unk64[i] = 1;
}

BEGIN_HANDLERS(ChordShapeGenerator)
    HANDLE(generate_chord_shape, OnGenerate)
    HANDLE(invert_chord_shape, OnInvert)
    HANDLE(set_string_fret, OnSetStringFret)
    HANDLE(get_string_trans, OnGetStringTrans)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x40A)
END_HANDLERS

BEGIN_PROPSYNCS(ChordShapeGenerator)
    SYNC_PROP(chord_source_mesh, mChordSrcMesh)
    SYNC_PROP(finger_source_mesh, mFingerSrcMesh)
    SYNC_PROP(base_cross_section, mBaseXSection)
    SYNC_PROP(contour_cross_section, mContourXSection)
    SYNC_PROP(base_height, mBaseHeight)
    SYNC_PROP(num_slots, mNumSlots)
    SYNC_PROP(string_0_fret, mStringFrets[0])
    SYNC_PROP(string_1_fret, mStringFrets[1])
    SYNC_PROP(string_2_fret, mStringFrets[2])
    SYNC_PROP(string_3_fret, mStringFrets[3])
    SYNC_PROP(string_4_fret, mStringFrets[4])
    SYNC_PROP(string_5_fret, mStringFrets[5])
    SYNC_PROP(string_0, mString0)
    SYNC_PROP(string_1, mString1)
    SYNC_PROP(string_2, mString2)
    SYNC_PROP(string_3, mString3)
    SYNC_PROP(string_4, mString4)
    SYNC_PROP(string_5, mString5)
    SYNC_PROP(fret_height_1, mFretHeights[1])
    SYNC_PROP(fret_height_2, mFretHeights[2])
    SYNC_PROP(fret_height_3, mFretHeights[3])
    SYNC_PROP(fret_height_4, mFretHeights[4])
    SYNC_PROP(fret_height_5, mFretHeights[5])
    SYNC_PROP(fret_height_6, mFretHeights[6])
    SYNC_PROP(grade_distance_1, mGradeDistances[1])
    SYNC_PROP(grade_distance_2, mGradeDistances[2])
    SYNC_PROP(grade_distance_3, mGradeDistances[3])
    SYNC_PROP(grade_distance_4, mGradeDistances[4])
    SYNC_PROP(grade_distance_5, mGradeDistances[5])
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS