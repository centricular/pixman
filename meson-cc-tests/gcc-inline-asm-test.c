int main () {
  asm volatile ( "\tnop\n" : : : "cc", "memory" );
  return 0;
}
