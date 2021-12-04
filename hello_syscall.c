#include "util.h"

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

const static char hello[] = "Hello, World\n";

void _start() {
    nostd_write(STDOUT_FD, hello, sizeof(hello) - 1);
    nostd_exit(EXIT_SUCCESS);
}
