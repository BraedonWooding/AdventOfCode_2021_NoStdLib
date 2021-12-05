#include <nostd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

const static char hello[] = "Hello World\n";

int _main(int argc, char *argv) {
    nostd_write(STDOUT_FD, hello, sizeof(hello) - 1);
    return EXIT_SUCCESS;
}
