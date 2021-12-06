#ifndef CHONKY_NOSTD
#define CHONKY_NOSTD

// Not cross platform and very bad
typedef unsigned long long size_t;

typedef unsigned char bool;
enum _bool {
    FALSE = 0,
    TRUE = 1,
};

int nostd_write(unsigned int fd, const char *buf, size_t len);

void nostd_exit(int code);

int nostd_intparse(char *buf);

unsigned int nostd_intparse_bin(char *buf);

int nostd_power_slow(int base, int power);

size_t nostd_strlen(char *buf);

int nostd_write_int(unsigned int fd, int n);

int nostd_write_char(unsigned int fd, char chr);

#endif /* CHONKY_NOSTD */
