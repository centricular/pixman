#include <stdlib.h>
#include <pthread.h>

static pthread_once_t once_control = PTHREAD_ONCE_INIT;
static pthread_key_t key;

static void
make_key (void)
{
  pthread_key_create (&key, NULL);
}

int
main ()
{
  void *value = NULL;

  if (pthread_once (&once_control, make_key) != 0)
  {
    value = NULL;
  }
  else
  {
    value = pthread_getspecific (key);
    if (!value)
    {
      value = malloc (100);
      pthread_setspecific (key, value);
    }
  }
  return 0;
}
