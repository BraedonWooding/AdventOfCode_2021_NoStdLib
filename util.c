#include "util.h"

int nostd_write(unsigned int fd, const char *buf, size_t len) {
    register int syscall_no             asm("rax") = 1;
    register unsigned int arg1_fd       asm("rdi") = fd;
    register const char *arg2_buf       asm("rsi") = buf;
    register size_t arg3_len            asm("rdx") = len;
    asm("syscall");

    // fall off end of non-void ends up returning %rax
    // which holds the result of the write syscall
}

int nostd_write_int(unsigned int fd, int n) {
    char buf[1024];
    // stupid implementation, presumes that n <= 1_000_000
    int bases[] = {
        1000000, 100000, 10000, 1000, 100, 10, 1
    };
    int p = 0;

    for (int i = 0; i < sizeof(bases) / sizeof(bases[0]); i++) {
        int mod = n / bases[i];
        if (mod || p) {
            buf[p++] = mod + '0';
            n -= mod * bases[i];
        }
    }

    if (p == 0) {
        buf[p++] = n + '0';
    }

    buf[p] = 0;
    nostd_write(fd, buf, p);
}

int nostd_write_char(unsigned int fd, char chr) {
    char buf[1];
    buf[0] = chr;
    nostd_write(fd, buf, 1);
}

/* No return */
void nostd_exit(int code) {
    register int syscall_no     asm("rax") = 60;
    register int arg1_err_code  asm("rdi") = code;

    asm("syscall");
}

size_t nostd_strlen(char *buf) {
    char *p;
    for (p = buf; *p; p++);
    return p - buf;
}

int nostd_power_slow(int base, int power) {
    int result = 1;
    for (int i = 0; i < power; i++) result *= base;
    return result;
}

/* Presuming input is valid ;) */
int nostd_intparse(char *buf) {
    int res = 0;
    size_t len = nostd_strlen(buf);

    for (int i = 0; i < len; i++) {
        res += nostd_power_slow(10, len - 1 - i) * (buf[i] - '0');
    }

    return res;
}
