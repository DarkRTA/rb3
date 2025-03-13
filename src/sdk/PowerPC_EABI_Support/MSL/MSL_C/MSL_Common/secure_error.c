#include <types.h>
void (*__msl_constraint_handler)(void);

void __msl_runtime_constraint_violation_s() {
    if (__msl_constraint_handler != NULL) {
        __msl_constraint_handler();
    }
}
