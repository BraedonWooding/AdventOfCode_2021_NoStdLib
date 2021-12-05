#include <nostd.h>

#define STDOUT_FD (1)
#define EXIT_SUCCESS (0)

int _main(int argc, char *argv[])
{
    int depth = 0;
    int position = 0;
    int aim = 0;

    for (char **p = &argv[1]; *p; p++)
    {
        // read instruction
        char *instr = *(p++);
        int amount = nostd_intparse(*p);
        switch (instr[0])
        {
        case 'f': /* forward */
            position += amount;
            depth += amount * aim;
            break;
        case 'd': /* down */
            aim += amount;
            break;
        case 'u': /* up */
            aim -= amount;
            break;
        default:
            break;
        }
    }

    nostd_write_int(STDOUT_FD, position * depth);
    nostd_write_char(STDOUT_FD, '\n');
    return EXIT_SUCCESS;
}
