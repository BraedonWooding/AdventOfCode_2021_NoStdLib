#include "util.h"

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

const static char hello[] = "Hello, World\n";

int _main(int argc, char *argv[]) {
    int acc = 0;
    int buf[3];
    int i = 0;
    int prev[3];

    prev[(0 + i) % 3] = nostd_intparse(argv[1]);
    prev[(1 + i) % 3] = nostd_intparse(argv[2]);
    prev[(2 + i) % 3] = nostd_intparse(argv[3]);
    i = 4;
    int prevSum = prev[0] + prev[1] + prev[2];

    while (i < argc) {
        buf[0] = prev[1];
        buf[1] = prev[2];
        buf[2] = nostd_intparse(argv[i]);
        int sum = buf[0] + buf[1] + buf[2];
        if (sum > prevSum) {
            acc++;
        }

        prevSum = sum;
        prev[0] = buf[0];
        prev[1] = buf[1];
        prev[2] = buf[2];
        i++;
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
