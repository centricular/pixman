#if !(defined(__mips__) &&  __mips_isa_rev >= 2)
#error MIPS DSPr2 is currently only available on MIPS32r2 platforms.
#endif
int
main ()
{
    int c = 0, a = 0, b = 0;
    __asm__ __volatile__ (
        "precr.qb.ph %[c], %[a], %[b]          \n\t"
        : [c] "=r" (c)
        : [a] "r" (a), [b] "r" (b)
    );
    return c;
}
