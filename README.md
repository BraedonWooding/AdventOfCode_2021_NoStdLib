# AdventOfCode_2021_NoStdLib

> By Braedon Wooding with help by Uber-Kryos

AOC/21 written without any standard library imports, uses syscalls (asm) if required

> Only works on Linux x86_64 though porting this onto AARCH/others won't be particularly hard.  Windows just would require syscall number updates

No promises on correctness, and a bunch of silly decisions are made for the sake of me not wanting to spend 100 hrs on this :)

## Roughly how it works

### _start

Since we can't use `main()` (that's a C stdlib thing) we have to roll our own.  We call it `_main` and the assembly to do so roughly looks like below;

```asm
.text
.globl _start
_start:
  popq %rdi           # argc
  movq %rsp, %rsi     # argv
  call _main
  movq %rax, %rdi     # exit code from _main
  call nostd_exit
```

### Syscall alternatives

It's pretty easy to call a syscall in C using inline assembly an example is below

```c
// nostd_write
register int syscall_no             asm("rax") = 1;
register unsigned int arg1_fd       asm("rdi") = fd;
register const char *arg2_buf       asm("rsi") = buf;
register size_t arg3_len            asm("rdx") = len;
asm("syscall");
```

So in most cases the difficulty is the lack of nice C stdlib functions around malloc/string & memory stuff.

### Memory Allocation

Is (manifesting my destiny) done through mmap + arena allocation or static mem.
