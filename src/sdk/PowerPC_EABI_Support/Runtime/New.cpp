#include <new>
#include <stdlib.h>
#include "decomp.h"

// Dummy implementations, these got deadstripped
// Names changed to prevent multiply-defined errors
// void *operator new(std::size_t size) {
void *operator_new(std::size_t size) {
    void* ptr = malloc(size);
    if (!ptr)
        throw std::bad_alloc();
    return ptr;
}

// void *operator new[](std::size_t size) {
void *operator_new_array(std::size_t size) {
    return operator_new(size);
}

// void operator delete(void *ptr) {
void operator_delete(void *ptr) {
    free(ptr);
}

// void operator delete[](void *ptr) {
void operator_delete_array(void *ptr) {
    free(ptr);
}
