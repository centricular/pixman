#if defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 2))
#   if !defined(__amd64__) && !defined(__x86_64__)
#      error "Need GCC >= 4.2 for SSE2 intrinsics on x86"
#   endif
#endif
#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
int param;
int main () {
    __m128i a = _mm_set1_epi32 (param), b = _mm_set1_epi32 (param + 1), c;
	c = _mm_xor_si128 (a, b);
    return _mm_cvtsi128_si32(c);
}
