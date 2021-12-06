#include <nostd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

void count(char *numbers[], int index, int length, int *ones_out, int *zeroes_out)
{
    for (char **p = numbers; p < numbers + length; p++)
    {
        int bit = (*p)[index] - '0';
        (*ones_out) += bit;
        (*zeroes_out) += !bit;
    }
}

int partition(char *numbers[], int length, int index, bool prefer_ones)
{
    // bubble sort on the index
    bool swapped = TRUE;
    while (swapped)
    {
        swapped = FALSE;
        for (int i = 0; i < length - 1; i++)
        {
            if (numbers[i][index] - '0' != numbers[i + 1][index] - '0')
            {
                if (numbers[i][index] - '0' == (prefer_ones ? 0 : 1))
                {
                    char *tmp = numbers[i];
                    numbers[i] = numbers[i + 1];
                    numbers[i + 1] = tmp;
                    swapped = TRUE;
                }
            }
        }
    }

    // calculate length
    int final_length = 0;
    while (final_length < length && numbers[final_length][index] - '0' == (prefer_ones ? 1 : 0))
        final_length++;

    return final_length;
}

int _main(int argc, char *argv[])
{
    int O2 = 0;
    int CO2 = 0;

    char **CO2_partition;
    char **O2_partition;
    int CO2_partition_length;
    int O2_partition_length;

    // all binary numbers are the same length
    int len = nostd_strlen(argv[1]);

    /*
        Without an easy source of allocation this becomes sort of tricky
        however, we can utilise sorting to reach a similar goal.

        We are going to partition the numbers at each stage to correspond to O2/CO2/<Junk>
        where Junk is just the stuff at the end of the array that no one cares about.

        Thus we can just take partitions of those arrays and use them.

        Just to make it harder for no reason, we'll process O2 and CO2 at the same time
        since they can occupy separate partitions in the array ;)

        In reality it'll look something like this;
           A | B | C | D | E
        => CO2 (A | B | C) O2 (D | E)
        => CO2 (A | B) JUNK (C) O2 (D) JUNK (E)
     */

    // the first iteration is manual since we need to define starting points for partitions
    {
        int ones = 0;
        int zeroes = 0;

        count(&argv[1], 0, argc - 1, &ones, &zeroes);
        O2_partition = &argv[1];
        O2_partition_length = argc - 1;
        O2_partition_length = partition(O2_partition, O2_partition_length, 0, ones >= zeroes);
        CO2_partition = O2_partition + O2_partition_length;
        CO2_partition_length = argc - 1 - O2_partition_length;

        if (ones >= zeroes)
        {
            O2 |= 1 << (len - 1);
            CO2 |= 0 << (len - 1);
        }
        else
        {
            O2 |= 0 << (len - 1);
            CO2 |= 1 << (len - 1);
        }
    }

    for (int i = 1; i < len; i++)
    {
        // count in each partition
        {
            // O2
            if (O2_partition_length == 1) {
                O2 |= (O2_partition[0][i] - '0') << (len - 1 - i);
            } else {
                int ones = 0;
                int zeroes = 0;
                count(O2_partition, i, O2_partition_length, &ones, &zeroes);
                O2_partition_length = partition(O2_partition, O2_partition_length, i, ones >= zeroes);
                O2 |= (ones >= zeroes) << (len - 1 - i);
            }
        }

        {
            // CO2
            if (CO2_partition_length == 1) {
                CO2 |= (CO2_partition[0][i] - '0') << (len - 1 - i);
            } else {
                int ones = 0;
                int zeroes = 0;
                count(CO2_partition, i, CO2_partition_length, &ones, &zeroes);
                CO2_partition_length = partition(CO2_partition, CO2_partition_length, i, ones < zeroes);
                CO2 |= (ones < zeroes) << (len - 1 - i);
            }
        }
    }

    nostd_write_int(STDOUT_FD, O2);
    nostd_write_char(STDOUT_FD, '\n');
    
    nostd_write_int(STDOUT_FD, CO2);
    nostd_write_char(STDOUT_FD, '\n');

    nostd_write_int(STDOUT_FD, O2 * CO2);
    nostd_write_char(STDOUT_FD, '\n');
    return EXIT_SUCCESS;
}
