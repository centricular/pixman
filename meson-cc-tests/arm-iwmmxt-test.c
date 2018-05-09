#ifndef __arm__
#error "IWMMXT is only available on ARM"
#endif
#ifndef __IWMMXT__
#error "IWMMXT not enabled (with -march=iwmmxt)"
#endif
#if defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 8))
#error "Need GCC >= 4.8 for IWMMXT intrinsics"
#endif
#include <mmintrin.h>
int main () {
	union {
		__m64 v;
		char c[8];
	} a = { .c = {1, 2, 3, 4, 5, 6, 7, 8} };
	int b = 4;
	__m64 c = _mm_srli_si64 (a.v, b);
}
