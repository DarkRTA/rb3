#include "buffer_io.h"

void __prep_buffer(FILE* file) {
    file->buffer_ptr = file->buffer;
    file->buffer_len = file->buffer_size - (file->position & file->buffer_alignment);
    file->buffer_pos = file->position;
}

int __flush_buffer(FILE* file, size_t* length) {
    int y, x = file->buffer - file->buffer_ptr;
    if (x) {
        file->buffer_len = x;
        y = file->write_proc(file->handle, file->buffer, (size_t*)&file->buffer_len, file->ref_con);
        if (length != 0) *length = file->buffer_len;
        if (y != 0) return y; else {
            file->position += file->buffer_len;
        }
    }
    file->buffer_len = file->buffer_size - (file->position & file->buffer_alignment);
    file->buffer_pos = file->position;
    return 0;
}

