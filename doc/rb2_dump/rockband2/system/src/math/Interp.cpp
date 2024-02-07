/*
    Compile unit: C:\rockband2\system\src\math\Interp.cpp
    Producer: MW EABI PPC C-Compiler
    Language: C++
    Code range: 0x8062D618 -> 0x8062DAB8
*/
// Range: 0x8062D618 -> 0x8062D654
void * LinearInterpolator::LinearInterpolator(class LinearInterpolator * const this /* r31 */) {
    // References
    // -> struct [anonymous] __vt__18LinearInterpolator;
}

// Range: 0x8062D654 -> 0x8062D664
void * LinearInterpolator::LinearInterpolator() {
    // References
    // -> struct [anonymous] __vt__18LinearInterpolator;
}

// Range: 0x8062D664 -> 0x8062D6C0
void LinearInterpolator::Reset() {
    // Local variables
    float run; // f4
}

// Range: 0x8062D6C0 -> 0x8062D77C
void LinearInterpolator::Reset(class LinearInterpolator * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x8062D77C -> 0x8062D84C
void * ATanInterpolator::ATanInterpolator(class ATanInterpolator * const this /* r31 */, float y0 /* f27 */, float y1 /* f28 */, float x0 /* f29 */, float x1 /* f30 */, float severity /* f31 */) {
    // References
    // -> struct [anonymous] __vt__16ATanInterpolator;
}

// Range: 0x8062D84C -> 0x8062D954
void ATanInterpolator::Reset(class ATanInterpolator * const this /* r31 */, float y0 /* f27 */, float y1 /* f28 */, float x0 /* f29 */, float x1 /* f30 */, float severity /* f31 */) {
    // Local variables
    float x0val; // f0
    float x1val; // f1
    float rise; // f2

    // References
    // -> class Debug TheDebug;
}

// Range: 0x8062D954 -> 0x8062DA68
void ATanInterpolator::Reset(class ATanInterpolator * const this /* r30 */, const class DataArray * data /* r31 */) {}

// Range: 0x8062DA68 -> 0x8062DAB8
float ATanInterpolator::Eval(class ATanInterpolator * const this /* r31 */) {
    // Local variables
    float xnorm; // f0
    float ydenorm; // f0
    float ynorm; // f1
}

struct {
    // total size: 0x14
} __vt__16ATanInterpolator; // size: 0x14, address: 0x8092FBDC
struct {
    // total size: 0x8
} __RTTI__16ATanInterpolator; // size: 0x8, address: 0x8092FC10
struct {
    // total size: 0x14
} __vt__18LinearInterpolator; // size: 0x14, address: 0x8092FC18
struct {
    // total size: 0x8
} __RTTI__18LinearInterpolator; // size: 0x8, address: 0x8092FC50
struct {
    // total size: 0x8
} __RTTI__12Interpolator; // size: 0x8, address: 0x8092FC68

