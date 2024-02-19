#ifndef _MSL_COMMON_FILE_STRUC_H
#define _MSL_COMMON_FILE_STRUC_H

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
#endif /* _MSL_WIDE_CHAR */

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
	__file_handle handle;                               // _00
	__file_modes mode;                                  // _04
	__file_state state;                                 // _08
	unsigned char is_dynamically_allowed;               // _0C
	unsigned char char_buffer;                          // _0D
	unsigned char char_buffer_overflow;                 // _0E
	unsigned char ungetc_buffer[__ungetc_buffer_size];  // _0F
	wchar_t ungetwc_buffer[__ungetc_buffer_size];       // _12
	unsigned int position;                              // _18
	unsigned char* buffer;                              // _1C
	unsigned int buffer_size;                           // _20
	unsigned char* buffer_ptr;                          // _24
	unsigned int buffer_len;                            // _28
	unsigned int buffer_alignment;                      // _2C
	unsigned int saved_buffer_len;                      // _30
	unsigned int buffer_pos;                            // _34
	__pos_proc position_proc;                           // _38
	__io_proc read_proc;                                // _3C
	__io_proc write_proc;                               // _40
	__close_proc close_proc;                            // _44
	__ref_con ref_con;                                  // _48
	_FILE* next_file_struct;                            // _4C
};

typedef struct _FILE FILE;


#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

// define standard C file pointer location names
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
