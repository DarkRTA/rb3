/*
    Compile unit: C:\products\RVL\runtime_libs\debugger\embedded\MetroTRK\Export\mslsupp.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8065DE00 -> 0x8065E3BC
*/
// Range: 0x8065DE00 -> 0x8065DEDC
int __position_file(unsigned long handle /* r28 */, unsigned long * position /* r29 */, int mode /* r30 */) {
    // Local variables
    unsigned char result; // r0
    unsigned char SeekMode; // r31
}

// Range: 0x8065DEDC -> 0x8065DF60
int __close_file(unsigned long handle /* r31 */) {
    // Local variables
    unsigned char result; // r0
}

// Range: 0x8065DF60 -> 0x8065E0DC
int __open_file(const char * name /* r29 */, struct {
    // total size: 0x4
    unsigned int open_mode : 2; // offset 0x0, size 0x4
    unsigned int io_mode : 3; // offset 0x0, size 0x4
    unsigned int buffer_mode : 2; // offset 0x0, size 0x4
    unsigned int file_kind : 3; // offset 0x0, size 0x4
    unsigned int file_orientation : 2; // offset 0x0, size 0x4
    unsigned int binary_io : 1; // offset 0x0, size 0x4
} & mode /* r30 */, unsigned long * handle /* r31 */) {
    // Local variables
    unsigned char result; // r0
}

// Range: 0x8065E0DC -> 0x8065E190
int __write_file(unsigned long handle /* r29 */, unsigned char * buffer /* r30 */, unsigned long * count /* r31 */) {}

// Range: 0x8065E190 -> 0x8065E244
int __read_file(unsigned long handle /* r29 */, unsigned char * buffer /* r30 */, unsigned long * count /* r31 */) {}

// Range: 0x8065E244 -> 0x8065E300
int __TRK_write_console(unsigned char * buffer /* r30 */, unsigned long * count /* r31 */) {}

// Range: 0x8065E300 -> 0x8065E3BC
int __read_console(unsigned char * buffer /* r30 */, unsigned long * count /* r31 */) {}

