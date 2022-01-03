# AdventOfCode_2021_NoStdLib

> By Braedon Wooding with help by Uber-Kryos

AOC/21 written without any standard library imports, uses syscalls (asm) if required

> Only works on Linux x86_64 though porting this onto AARCH/others won't be particularly hard.  Windows just would require syscall number updates

No promises on correctness, and a bunch of silly decisions are made for the sake of me not wanting to spend 100 hrs on this :)

## Roughly how it works

### _start

Since we can't use `main()` (that's a C stdlib thing) we have to roll our own.  We call it `_main` and the assembly to do so roughly looks like below;

```c
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
```

### Syscall alternatives

It's pretty easy to call a syscall in C using inline assembly an example is below

```c
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
    // we either let the return fall off, since 'rax' should already
    // have the correct value from the syscall, or we'll just create a temporary
    // and write to that from rax then return that... I'm not sure which is more correct
    // but they both seem to work.
}
```

So in most cases the difficulty is the lack of nice C stdlib functions around malloc/string & memory stuff.

### Memory Allocation

Hopefully, none :).
