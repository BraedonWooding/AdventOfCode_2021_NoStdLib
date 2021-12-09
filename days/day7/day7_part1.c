#include <nostd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

unsigned int intparse(void *a)
{
    return nostd_intparse((char*)a);
}

int _main(int argc, char *argv[])
{
    // sort the list
    nostd_radix_sort((void**)&argv[1], argc - 1, intparse);

    // for (int i = 1; i < argc; i++) {
    //     nostd_write_int(STDOUT_FD, nostd_intparse(argv[i]));
    //     nostd_write_char(STDOUT_FD, '\n');
    // }

    // find median
    int median;
    if ((argc - 1) % 2 == 0) {
        int higher = nostd_intparse(argv[1 + ((argc - 1)) / 2]);
        int lower = nostd_intparse(argv[1 + ((argc - 1)) / 2 - 1]);
        median = (higher + lower) / 2;
    } else {
        median = nostd_intparse(argv[1 + ((argc - 1)) / 2]);
    }

    nostd_write_int(STDOUT_FD, median);
    nostd_write_char(STDOUT_FD, '\n');

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += nostd_iabs(median - nostd_intparse(argv[i]));
    }
    
    nostd_write_int(STDOUT_FD, sum);
    nostd_write_char(STDOUT_FD, '\n');

    return EXIT_SUCCESS;
}
