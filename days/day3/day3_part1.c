#include <nostd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

int _main(int argc, char *argv[])
{
    int gamma = 0;
    int epsilon = 0;

    // all binary numbers are the same length
    int len = nostd_strlen(argv[1]);
    for (int i = 0; i < len; i++)
    {
        int ones = 0;
        int zeroes = 0;

        for (char **p = &argv[1]; *p; p++)
        {
            int bit = (*p)[i] - '0';
            ones += bit;
            zeroes += !bit;
        }

        if (ones > zeroes) {
            gamma |= 1 << (len - 1 - i);
            epsilon |= 0 << (len - 1 - i);
        } else {
            gamma |= 0 << (len - 1 - i);
            epsilon |= 1 << (len - 1 - i);
        }
    }

    nostd_write_int(STDOUT_FD, gamma * epsilon);
    nostd_write_char(STDOUT_FD, '\n');
    return EXIT_SUCCESS;
}
