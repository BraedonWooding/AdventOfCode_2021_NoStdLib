C_INCLUDE_PATH=-I../../nostd
CFLAGS=-nostdinc -nostdlib -fno-builtin -g $(C_INCLUDE_PATH)
LDFLAGS=-lc

default: day7_part1 day7_part2

day7_part1: day7_part1.o nostd
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) day7_part1.o ../../nostd/nostd.o -o day7_part1

day7_part2: day7_part2.o nostd
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) day7_part2.o ../../nostd/nostd.o -o day7_part2

# not a great solution, will cause excessive rebuilds... it's fine though
nostd: ../../nostd/nostd.o
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) -c

.PHONY: clean
clean:
	rm *.o hello_world hello_unix hello_nostd
