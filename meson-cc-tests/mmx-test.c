#if defined(__GNUC__) && (__GNUC__ < 3 || (__GNUC__ == 3 && __GNUC_MINOR__ < 4))
#error "Need GCC >= 3.4 for MMX intrinsics"
#endif
#include <mmintrin.h>
#include <stdint.h>

/* Check support for block expressions */
#define _mm_shuffle_pi16(A, N)						\
  ({									\
   __m64 ret;							\
   \
   /* Some versions of clang will choke on K */ 			\
   asm ("pshufw %2, %1, %0\n\t"					\
       : "=y" (ret)						\
       : "y" (A), "K" ((const int8_t)N)				\
       );								\
       \
       ret;								\
       })

int main () {
  __m64 v = _mm_cvtsi32_si64 (1);
  __m64 w;

  w = _mm_shuffle_pi16(v, 5);

  /* Some versions of clang will choke on this */
  asm ("pmulhuw %1, %0\n\t"
      : "+y" (w)
      : "y" (v)
      );

  return _mm_cvtsi64_si32 (v);
}
