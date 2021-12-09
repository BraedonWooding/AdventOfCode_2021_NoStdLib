#include <nostd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

unsigned int intparse(void *a)
{
    return nostd_intparse((char*)a);
}

int _main(int argc, char *argv[])
{
    /*
        This is insanely clever, thanks to Uber-Kryos for his genius.

        n^2 / 2 + n / 2 => n / 2 ~~ n^2 / 2

        n * (n + 1)/2 <= n^2, but we'll approximate it as n^2
        this is a stupid approximation, but the grace of god
        it somehow goddamn works.

        minarg_Y(|Y - x1| + |Y - x2| + ...) = median(x)
        minarg_Y(|Y - x1|^2 + |Y - x2|^2 + ...) = avg(x)

        If you want higher precision you would need to resolve
        n * (n + 1) / 2 = (n^2)/2 + n/2

        minarg_Y((n_1^2 + n_1 + ...) / 2)
            = minarg_Y((n_1^2 + n_2^2 + ... + n_1 + n_2 + ...)) / 2
        which doesn't feel nice, so sadly I don't think you'll be able to
        resolve this any easier...
     */

    // find average
    int average;
    
    int sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += nostd_intparse(argv[i]);
    }
    average = sum / (argc - 1);

    int totalCost = 0;
    for (int i = 1; i < argc; i++) {
        int n = nostd_iabs(average - nostd_intparse(argv[i]));
        totalCost += (n * (n + 1)) / 2;
    }

    // real soln would have to handle the case of ceiling as well as floor here...
    
    nostd_write_int(STDOUT_FD, totalCost);
    nostd_write_char(STDOUT_FD, '\n');

    return EXIT_SUCCESS;
}
