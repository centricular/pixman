#ifndef __mips_loongson_vector_rev
#error "Loongson Multimedia Instructions are only available on Loongson"
#endif
#if defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4))
#error "Need GCC >= 4.4 for Loongson MMI compilation"
#endif
#include "pixman/loongson-mmintrin.h"
int main () {
    union {
        __m64 v;
        char c[8];
    } a = { .c = {1, 2, 3, 4, 5, 6, 7, 8} };
    int b = 4;
    __m64 c = _mm_srli_pi16 (a.v, b);
    return 0;
}
