unsigned int __attribute__ ((vector_size(16))) e, a, b;
int main (void) { e = a - ((b << 27) + (b >> (32 - 27))) + 1; return e[0]; }
