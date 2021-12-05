#include <unistd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

const static char hello[] = "Hello World\n";

void _start() {
    // prevents gcc's erroneous (imo) 'unused result'
    // clang picks up on just the '(void)' but gcc requires
    // you to actually use the result in an expression
    (void)!write(STDOUT_FD, hello, sizeof(hello) - 1);
    _exit(EXIT_SUCCESS);
}
