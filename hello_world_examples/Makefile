C_INCLUDE_PATH=-I../nostd
CFLAGS=-Os -s -nostdinc -nostdlib -fno-stack-protector -fno-builtin -g $(C_INCLUDE_PATH)
LDFLAGS=-lc

default: hello_world hello_nostd hello_unix

hello_world: CFLAGS = -Os -s
hello_world: hello_world.o
	gcc $(INC) hello_world.o -o hello_world

hello_unix: CFLAGS = -Os -s -nostartfiles
hello_unix: hello_unix.o
	gcc $(CFLAGS) hello_unix.o -o hello_unix

hello_nostd: hello_nostd.o nostd
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) hello_nostd.o ../nostd/nostd.o -o hello_nostd

# not a great solution, will cause excessive rebuilds... it's fine though
nostd: ../nostd/nostd.o
	gcc $(CFLAGS) $(LDFLAGS) $(C_INCLUDE_PATH) -c

.PHONY: clean
clean:
	rm *.o hello_world hello_unix hello_nostd
