#include "util.h"

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

const static char hello[] = "Hello, World\n";

int _main(int argc, char *argv[]) {
    int prev = 0;
    int acc = 0;

    for (char **p = &argv[1]; *p; p++) {
        int parsed = nostd_intparse(*p);

        if (p != &argv[1] && parsed > prev) {
            acc++;
        }

        prev = parsed;
    }

    nostd_write_int(STDOUT_FD, acc);
    nostd_write_char(STDOUT_FD, '\n');
    return EXIT_SUCCESS;
}

asm(
    ".text\n"
    ".globl _start\n"
    "_start:\n"
    "popq %rdi\n"
    "movq %rsp, %rsi\n"
    "callq _main\n"
    "movq %rax, %rdi\n"
    "callq nostd_exit\n"
);

void _start();
