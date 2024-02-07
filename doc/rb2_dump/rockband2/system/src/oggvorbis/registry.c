/*
    Compile unit: C:\rockband2\system\src\oggvorbis\registry.c
    Producer: MW EABI PPC C-Compiler
    Language: C89
    Code range: 0x80549394 -> 0x80549394
*/
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
} * _floor_P[2]; // size: 0x8, address: 0x8090F3D8
struct {
    // total size: 0x20
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
    long * * (* class)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x14, size 0x4
    int (* forward)(struct vorbis_block *, void *, float * *, float * *, int *, int, long * *); // offset 0x18, size 0x4
    int (* inverse)(struct vorbis_block *, void *, float * *, int *, int); // offset 0x1C, size 0x4
} * _residue_P[3]; // size: 0xC, address: 0x8090F3E0
struct {
    // total size: 0x14
    void (* pack)(struct vorbis_info *, void *, struct {
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
    void (* free_info)(void *); // offset 0x8, size 0x4
    int (* forward)(struct vorbis_block *); // offset 0xC, size 0x4
    int (* inverse)(struct vorbis_block *, void *); // offset 0x10, size 0x4
} * _mapping_P[1]; // size: 0x4, address: 0x80A47530

