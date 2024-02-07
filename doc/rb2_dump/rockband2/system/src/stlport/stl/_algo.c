/*
    Compile unit: C:\rockband2\system\src\stlport\stl\_algo.c
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x80625F90 -> 0x80626614
*/
// Range: 0x80625F90 -> 0x80626024
void sort(struct CuePoint * __first /* r29 */, struct CuePoint * __last /* r30 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r31 */) {}

// Range: 0x80626024 -> 0x806260AC
void __final_insertion_sort(struct CuePoint * __first /* r29 */, struct CuePoint * __last /* r30 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r31 */) {}

// Range: 0x806260AC -> 0x8062611C
void __unguarded_insertion_sort_aux(struct CuePoint * __last /* r29 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r30 */) {
    // Local variables
    struct CuePoint * __i; // r31
}

// Range: 0x8062611C -> 0x806261B0
void __unguarded_linear_insert(struct CuePoint * __last /* r28 */, struct CuePoint & __val /* r29 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r30 */) {
    // Local variables
    struct CuePoint * __next; // r31
}

// Range: 0x806261B0 -> 0x806262C0
void __insertion_sort(struct CuePoint * __first /* r28 */, struct CuePoint * __last /* r29 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r30 */) {
    // Local variables
    struct CuePoint * __i; // r31
}

// Range: 0x806262C0 -> 0x8062643C
void __introsort_loop(struct CuePoint * __first /* r27 */, struct CuePoint * __last /* r28 */, long __depth_limit /* r29 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r30 */) {
    // Local variables
    struct CuePoint * __cut; // r31
}

// Range: 0x8062643C -> 0x80626520
struct CuePoint * __unguarded_partition(struct CuePoint * __first /* r28 */, struct CuePoint * __last /* r29 */, struct CuePoint & __pivot /* r30 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r31 */) {}

// Range: 0x80626520 -> 0x8062652C
void partial_sort() {}

// Range: 0x8062652C -> 0x80626614
void __partial_sort(struct CuePoint * __first /* r27 */, struct CuePoint * __middle /* r28 */, struct CuePoint * __last /* r29 */, unsigned char (* __comp)(struct CuePoint &, struct CuePoint &) /* r30 */) {
    // Local variables
    struct CuePoint * __i; // r31
}


