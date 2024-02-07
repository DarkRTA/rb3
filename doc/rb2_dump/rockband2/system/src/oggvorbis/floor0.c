/*
    Compile unit: C:\rockband2\system\src\oggvorbis\floor0.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x8054001C -> 0x80540844
*/
// Range: 0x8054001C -> 0x80540060
static void floor0_free_info() {
    // Local variables
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * info; // r31
}

// Range: 0x80540060 -> 0x805400E0
static void floor0_free_look() {
    // Local variables
    struct {
        // total size: 0x20
        int ln; // offset 0x0, size 0x4
        int m; // offset 0x4, size 0x4
        int * * linearmap; // offset 0x8, size 0x4
        int n[2]; // offset 0xC, size 0x8
        struct {
            // total size: 0x60
            int order; // offset 0x0, size 0x4
            long rate; // offset 0x4, size 0x4
            long barkmap; // offset 0x8, size 0x4
            int ampbits; // offset 0xC, size 0x4
            int ampdB; // offset 0x10, size 0x4
            int numbooks; // offset 0x14, size 0x4
            int books[16]; // offset 0x18, size 0x40
            float lessthan; // offset 0x58, size 0x4
            float greaterthan; // offset 0x5C, size 0x4
        } * vi; // offset 0x14, size 0x4
        long bits; // offset 0x18, size 0x4
        long frames; // offset 0x1C, size 0x4
    } * look; // r31
}

// Range: 0x805400E0 -> 0x8054020C
static void * floor0_unpack(struct {
    // total size: 0x14
    long endbyte; // offset 0x0, size 0x4
    int endbit; // offset 0x4, size 0x4
    unsigned char * buffer; // offset 0x8, size 0x4
    unsigned char * ptr; // offset 0xC, size 0x4
    long storage; // offset 0x10, size 0x4
} * opb /* r27 */) {
    // Local variables
    struct codec_setup_info * ci; // r30
    int j; // r29
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * info; // r28
}

// Range: 0x8054020C -> 0x80540528
static void floor0_map_lazy_init(void * infoX /* r26 */, struct {
    // total size: 0x20
    int ln; // offset 0x0, size 0x4
    int m; // offset 0x4, size 0x4
    int * * linearmap; // offset 0x8, size 0x4
    int n[2]; // offset 0xC, size 0x8
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * vi; // offset 0x14, size 0x4
    long bits; // offset 0x18, size 0x4
    long frames; // offset 0x1C, size 0x4
} * look /* r27 */) {
    // Local variables
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * info; // r0
    int W; // r0
    int n; // r29
    int j; // r28
    float scale; // f31
    int val; // r4
}

// Range: 0x80540528 -> 0x80540590
static void * floor0_look(void * i /* r30 */) {
    // Local variables
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * info; // r0
    struct {
        // total size: 0x20
        int ln; // offset 0x0, size 0x4
        int m; // offset 0x4, size 0x4
        int * * linearmap; // offset 0x8, size 0x4
        int n[2]; // offset 0xC, size 0x8
        struct {
            // total size: 0x60
            int order; // offset 0x0, size 0x4
            long rate; // offset 0x4, size 0x4
            long barkmap; // offset 0x8, size 0x4
            int ampbits; // offset 0xC, size 0x4
            int ampdB; // offset 0x10, size 0x4
            int numbooks; // offset 0x14, size 0x4
            int books[16]; // offset 0x18, size 0x40
            float lessthan; // offset 0x58, size 0x4
            float greaterthan; // offset 0x5C, size 0x4
        } * vi; // offset 0x14, size 0x4
        long bits; // offset 0x18, size 0x4
        long frames; // offset 0x1C, size 0x4
    } * look; // r31
}

// Range: 0x80540590 -> 0x8054076C
static void * floor0_inverse1(struct vorbis_block * vb /* r29 */, void * i /* r30 */) {
    // Local variables
    struct {
        // total size: 0x20
        int ln; // offset 0x0, size 0x4
        int m; // offset 0x4, size 0x4
        int * * linearmap; // offset 0x8, size 0x4
        int n[2]; // offset 0xC, size 0x8
        struct {
            // total size: 0x60
            int order; // offset 0x0, size 0x4
            long rate; // offset 0x4, size 0x4
            long barkmap; // offset 0x8, size 0x4
            int ampbits; // offset 0xC, size 0x4
            int ampdB; // offset 0x10, size 0x4
            int numbooks; // offset 0x14, size 0x4
            int books[16]; // offset 0x18, size 0x40
            float lessthan; // offset 0x58, size 0x4
            float greaterthan; // offset 0x5C, size 0x4
        } * vi; // offset 0x14, size 0x4
        long bits; // offset 0x18, size 0x4
        long frames; // offset 0x1C, size 0x4
    } * look; // r0
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * info; // r31
    int j; // r31
    int k; // r3
    int ampraw; // r0
    float amp; // f31
    int booknum; // r0
    struct codebook * b; // r28
    float last; // f30
    float * lsp; // r27
}

// Range: 0x8054076C -> 0x80540844
static int floor0_inverse2(struct vorbis_block * vb /* r27 */, void * memo /* r28 */, float * out /* r29 */) {
    // Local variables
    struct {
        // total size: 0x20
        int ln; // offset 0x0, size 0x4
        int m; // offset 0x4, size 0x4
        int * * linearmap; // offset 0x8, size 0x4
        int n[2]; // offset 0xC, size 0x8
        struct {
            // total size: 0x60
            int order; // offset 0x0, size 0x4
            long rate; // offset 0x4, size 0x4
            long barkmap; // offset 0x8, size 0x4
            int ampbits; // offset 0xC, size 0x4
            int ampdB; // offset 0x10, size 0x4
            int numbooks; // offset 0x14, size 0x4
            int books[16]; // offset 0x18, size 0x40
            float lessthan; // offset 0x58, size 0x4
            float greaterthan; // offset 0x5C, size 0x4
        } * vi; // offset 0x14, size 0x4
        long bits; // offset 0x18, size 0x4
        long frames; // offset 0x1C, size 0x4
    } * look; // r31
    struct {
        // total size: 0x60
        int order; // offset 0x0, size 0x4
        long rate; // offset 0x4, size 0x4
        long barkmap; // offset 0x8, size 0x4
        int ampbits; // offset 0xC, size 0x4
        int ampdB; // offset 0x10, size 0x4
        int numbooks; // offset 0x14, size 0x4
        int books[16]; // offset 0x18, size 0x40
        float lessthan; // offset 0x58, size 0x4
        float greaterthan; // offset 0x5C, size 0x4
    } * info; // r30
    float * lsp; // r0
    float amp; // f1
}

struct {
    // total size: 0x1C
    void (* pack)(void *, struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } *); // offset 0x0, size 0x4
    void * (* unpack)(struct vorbis_info *, struct {
        // total size: 0x14
        long endbyte; // offset 0x0, size 0x4
        int endbit; // offset 0x4, size 0x4
        unsigned char * buffer; // offset 0x8, size 0x4
        unsigned char * ptr; // offset 0xC, size 0x4
        long storage; // offset 0x10, size 0x4
    } *); // offset 0x4, size 0x4
    void * (* look)(struct vorbis_dsp_state *, void *); // offset 0x8, size 0x4
    void (* free_info)(void *); // offset 0xC, size 0x4
    void (* free_look)(void *); // offset 0x10, size 0x4
    void * (* inverse1)(struct vorbis_block *, void *); // offset 0x14, size 0x4
    int (* inverse2)(struct vorbis_block *, void *, void *, float *); // offset 0x18, size 0x4
} floor0_exportbundle; // size: 0x1C, address: 0x80908770

