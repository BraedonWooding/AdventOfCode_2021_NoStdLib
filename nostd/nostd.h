#ifndef CHONKY_NOSTD
#define CHONKY_NOSTD

// Not cross platform and very bad
typedef unsigned long long size_t;

typedef unsigned char bool;
enum _bool
{
    FALSE = 0,
    TRUE = 1,
};

int nostd_iabs(int);

void nostd_radix_sort(void *elements[], int len, unsigned int (*fn_sort)(void *a));

int nostd_write(unsigned int fd, const char *buf, size_t len);

void nostd_exit(int code);

int nostd_intparse(char *buf);

unsigned int nostd_intparse_bin(char *buf);

int nostd_power_slow(int base, int power);

size_t nostd_strlen(char *buf);

int nostd_write_int(unsigned int fd, int n);

int nostd_write_char(unsigned int fd, char chr);

typedef unsigned int mode_t;

typedef enum mode_class
{
    CLASS_OTHER = 0x0,
    CLASS_GROUP = 0x3,
    CLASS_OWNER = 0x6,
} mode_class_t;

typedef enum mode_permission
{
    PERMISSION_EXECUTE = 0x0,
    PERMISSION_WRITE = 0x1,
    PERMISSION_READ = 0x2,
} mode_permission_t;

#define O_ACCMODE 0003
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define O_EXCL 0200
#define O_NOCTTY 0400
#define O_TRUNC 01000
#define O_APPEND 02000
#define O_NONBLOCK 04000
#define O_NDELAY O_NONBLOCK
#define O_SYNC 04010000
#define O_FSYNC O_SYNC
#define O_ASYNC 020000

typedef int open_flags_t;

mode_t perm_to_mode(mode_class_t class, mode_permission_t perm);

int nostd_open(const char *path, open_flags_t flags, mode_t mode);
int nostd_read(int fd, void *buf, size_t count);
int nostd_close(int fd);

#endif /* CHONKY_NOSTD */
