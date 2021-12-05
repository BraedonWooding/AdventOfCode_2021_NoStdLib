C_INCLUDE_PATH=-I../../nostd
CFLAGS=-Os -s -nostdinc -nostdlib -fno-stack-protector -fno-builtin -g $(C_INCLUDE_PATH)
LDFLAGS=-lc

default: day1_part1 day1_part2

day1_part1: day1_part1.o nostd
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) day1_part1.o ../../nostd/nostd.o -o day1_part1

day1_part2: day1_part2.o nostd
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) day1_part2.o ../../nostd/nostd.o -o day1_part2

# not a great solution, will cause excessive rebuilds... it's fine though
nostd: ../../nostd/nostd.o
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) -c

.PHONY: clean
clean:
	rm *.o hello_world hello_unix hello_nostd
