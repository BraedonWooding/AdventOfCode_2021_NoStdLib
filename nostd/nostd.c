#include "nostd.h"

int nostd_write(unsigned int fd, const char *buf, size_t len)
{
    asm(
        "movq $1, %%rax\n"
        "movq %0, %%rdi\n"
        "movq %1, %%rsi\n"
        "movq %2, %%rdx\n"
        "syscall\n"
        :
        : "r"((size_t)fd), "r"((size_t)buf), "r"((size_t)len)
        : "%rdi", "%rsi", "%rdx");
}

int nostd_write_int(unsigned int fd, int n)
{
    if (n < 0)
    {
        int amount = nostd_write_char(fd, '-');
        amount += nostd_write_int(fd, -n);
        return amount;
    }

    char buf[1024];
    // stupid implementation, presumes that n <= 1_000_000
    int bases[] = {
        1000000000, 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 //
    };
    int p = 0;

    for (int i = 0; i < sizeof(bases) / sizeof(bases[0]); i++)
    {
        int mod = n / bases[i];
        if (mod || p)
        {
            buf[p++] = mod + '0';
            n -= mod * bases[i];
        }
    }

    if (p == 0)
    {
        buf[p++] = n + '0';
    }

    buf[p] = 0;
    return nostd_write(fd, buf, p);
}

int nostd_write_char(unsigned int fd, char chr)
{
    char buf[1];
    buf[0] = chr;
    nostd_write(fd, buf, 1);
}

/* No return */
void nostd_exit(int code)
{
    asm(
        "movq $60, %%rax\n"
        "movq %0, %%rdi\n"
        "syscall\n"
        :
        : "r"((size_t)code)
        : "%rdi");
}

size_t nostd_strlen(char *buf)
{
    if (!buf)
        return 0;

    char *p;
    for (p = buf; *p; p++)
    {
    }
    return p - buf;
}

int nostd_power_slow(int base, int power)
{
    int result = 1;
    for (int i = 0; i < power; i++)
        result *= base;
    return result;
}

void nostd_radix_sort_rec(void *elements[], int len, int bit, unsigned int (*fn_parse)(void *a));

void nostd_radix_sort(void *elements[], int len, unsigned int (*fn_parse)(void *a))
{
    if (len == 0)
        return;

    // We are presuming little endian because we are cute lil programmers
    // who don't believe that servers exist ;)

    // We are going to be some cool mutha'f**ckers and implement binary quicksort
    // also known as in-place MSD radix sort implements
    nostd_radix_sort_rec(elements, len, 31, fn_parse);
}

int nostd_iabs(int n)
{
    if (n < 0)
        return -n;
    return n;
}

void nostd_radix_sort_rec(void *elements[], int len, int bit, unsigned int (*fn_parse)(void *a))
{
    if (len <= 1 || bit < 0)
        return;

    // we define 2 bins, the first one is for 0s and the second is for 1s
    // 0 grows forwards, and 1 grows backwards
    // for consistency the operation is *(++/-- bin) = element
    void **_1_bin = elements - 1;
    void **_0_bin = &elements[len];
    int _0_len = 0;
    int _1_len = 0;

    // I could do 11 here *for speed*, but for the sake of all that is good
    // in this little world, I'll preserve my future sanity instead ;)
    // you may argue len is 64 bit and thus I should support 64 bit
    // and to that I say; no.
    while (_0_bin - _1_bin > 1)
    {
        unsigned int parsed = fn_parse(_1_bin[1]);
        if (parsed & (1 << bit))
        {
            // this means that we have a 1 bit in this position
            // which means that we want to push it to the 1 bin
            // this is no real work
            _1_bin++;
            _1_len++;
        }
        else
        {
            // otherwise we want to push it to the end
            // so we'll do this by swapping it with the _0_bin
            void *tmp = *(--_0_bin);
            *_0_bin = _1_bin[1];
            _1_bin[1] = tmp;
            _0_len++;
        }
    }

    nostd_radix_sort_rec(elements, _1_len, bit - 1, fn_parse);
    nostd_radix_sort_rec(_0_bin, _0_len, bit - 1, fn_parse);
}

unsigned int nostd_intparse_bin(char *buf)
{
    unsigned int res = 0;
    size_t len = nostd_strlen(buf);

    for (int i = len - 1; i >= 0; i--)
    {
        // convert binary '1'/'0' to 1/0 then shift into place
        res |= ((buf[i] - '0') << (len - 1 - i));
    }

    return res;
}

/* Presuming input is valid ;) */
int nostd_intparse(char *buf)
{
    int res = 0;
    size_t len = nostd_strlen(buf);

    for (int i = 0; i < len; i++)
    {
        res += nostd_power_slow(10, len - 1 - i) * (buf[i] - '0');
    }

    return res;
}

int nostd_read(int fd, void *buf, size_t count)
{
    int ret;
    asm(
        "movq $0, %%rax\n"
        "movl %1, %%edi\n"
        "movq %2, %%rsi\n"
        "movq %3, %%rdx\n"
        "syscall\n"
        "movl %%eax, %0\n"
        : "=r"(ret)
        : "r"((int)fd), "r"((size_t)buf), "r"((size_t)count)
        : "%edi", "%rsi", "%rdx");
    return ret;
}

int nostd_close(int fd)
{
    asm(
        "movq $3, %%rax\n"
        "movl %0, %%edi\n"
        "syscall\n"
        :
        : "r"((int)fd)
        : "%edi");
}

int nostd_open(const char *path, open_flags_t flags, mode_t mode)
{
    int ret;
    asm(
        "movq $2, %%rax\n"
        "movq %1, %%rdi\n"
        "movq %2, %%rsi\n"
        "movq %3, %%rdx\n"
        "syscall\n"
        "movl %%eax, %0\n"
        : "=r"(ret)
        : "r"(path), "r"((long int)flags), "r"((long unsigned int)mode)
        : "%rdi", "%rsi", "%rdx");
    return ret;
}

mode_t perm_to_mode(mode_class_t class, mode_permission_t perm)
{
    return 1 << (perm + class);
}

int _main(int argc, char *argv[]);

__attribute__((naked)) void _start()
{
    asm(
        "xorl %%eax, %%eax\n"
        "popq %%rdi\n"
        "movq %%rsp, %%rsi\n"
        "callq _main\n"
        "movq %%rax, %%rdi\n"
        "call %P0"
        :
        : "i"(nostd_exit)
        : "%rdi", "%rax");
}
