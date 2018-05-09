#if defined(__GNUC__) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7))
/* attribute 'constructor' is supported since gcc 2.7, but some compilers
 * may only pretend to be gcc, so let's try to actually use it
 */
static int x = 1;
static void __attribute__((constructor)) constructor_function () { x = 0; }
int main (void) { return x; }
#else
#error not gcc or gcc version is older than 2.7
#endif
