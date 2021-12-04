#include <unistd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

const static char hello[] = "Hello, World\n";

void _start() {
    write(STDOUT_FD, hello, sizeof(hello) - 1);
    _exit(EXIT_SUCCESS);
}
