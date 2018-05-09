#include <mmintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <tmmintrin.h>
int param;
int main () {
    __m128i a = _mm_set1_epi32 (param), b = _mm_set1_epi32 (param + 1), c;
    c = _mm_maddubs_epi16 (a, b);
    return _mm_cvtsi128_si32(c);
}
