#ifndef _MSL_FILE_DEF_H
#define _MSL_FILE_DEF_H

#include "size_def.h"
#include "wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long __file_handle;
typedef unsigned long fpos_t;
typedef struct _FILE _FILE, *P_FILE;

#define __ungetc_buffer_size 2

enum __file_kinds {
    __closed_file,
    __disk_file,
    __console_file,
    __unavailable_file
};

enum __open_modes {
    __must_exist,
    __create_if_necessary,
    __create_or_truncate
};

enum __file_orientation {
    __unoriented,
    __char_oriented,
    __wide_oriented
};

enum __io_modes {
    __read = 1,
    __write = 2,
    __read_write = 3,
    __append = 4
};

typedef struct __file_modes {
    unsigned int open_mode : 2;
    unsigned int io_mode : 3;
    unsigned int buffer_mode : 2;
    unsigned int file_kind : 3;

#ifdef _MSL_WIDE_CHAR
    unsigned int file_orientation : 2;
#endif

    unsigned int binary_io : 1;
} __file_modes;

enum __io_states {
    __neutral,
    __writing,
    __reading,
    __rereading
};

typedef struct __file_state {
    unsigned int io_state : 3;
    unsigned int free_buffer : 1;
    unsigned char eof;
    unsigned char error;
} __file_state;

typedef void* __ref_con;
typedef void (*__idle_proc)(void);
typedef int (*__pos_proc)(__file_handle file, fpos_t* position, int mode, __ref_con ref_con);
typedef int (*__io_proc)(__file_handle file, unsigned char* buff, size_t* count, __ref_con ref_con);
typedef int (*__close_proc)(__file_handle file);

struct _FILE {
    __file_handle handle;                               /* 0x00 */
    __file_modes mode;                                  /* 0x04 */
    __file_state state;                                 /* 0x08 */
    unsigned char is_dynamically_allowed;               /* 0x0C */
    unsigned char char_buffer;                          /* 0x0D */
    unsigned char char_buffer_overflow;                 /* 0x0E */
    unsigned char ungetc_buffer[__ungetc_buffer_size];  /* 0x0F */
    wchar_t ungetwc_buffer[__ungetc_buffer_size];       /* 0x12 */
    unsigned int position;                              /* 0x18 */
    unsigned char* buffer;                              /* 0x1C */
    unsigned int buffer_size;                           /* 0x20 */
    unsigned char* buffer_ptr;                          /* 0x24 */
    unsigned int buffer_len;                            /* 0x28 */
    unsigned int buffer_alignment;                      /* 0x2C */
    unsigned int saved_buffer_len;                      /* 0x30 */
    unsigned int buffer_pos;                            /* 0x34 */
    __pos_proc position_proc;                           /* 0x38 */
    __io_proc read_proc;                                /* 0x3C */
    __io_proc write_proc;                               /* 0x40 */
    __close_proc close_proc;                            /* 0x44 */
    __ref_con ref_con;                                  /* 0x48 */
    _FILE* next_file_struct;                            /* 0x4C */
};

typedef struct _FILE FILE;


#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

/* define standard C file pointer location names */
#define SEEK_SET (0)
#define SEEK_CUR (1)
#define SEEK_END (2)

#define stdin &(__files[0])
#define stdout &(__files[1])
#define stderr &(__files[2])

#define _STATIC_FILES 4

extern FILE __files[];

#ifdef __cplusplus
}
#endif

#endif
