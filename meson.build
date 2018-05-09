project('pixman', 'c',
  version : '0.35.1',
  meson_version : '>= 0.46',
  default_options: [ 'buildtype=debugoptimized'],
)

pkgmod = import('pkgconfig')

check_sizeofs = [
  ['long'],
]

check_optional_deps = [
  ['openmp', {'conf-prefix': 'use'}],
  ['gtk', {'pkg': 'gtk+-2.0', 'version': '>= 2.16'}],
  ['libpng'],
]

check_funcs = [
  ['getisax'],
  ['posix_memalign'],
  ['sigaction'],
  ['alarm'],
  ['mmap'],
  ['mprotect'],
  ['getpagesize'],
  ['feenableexcept', {'link_with': ['m']}],
  ['gettimeofday'],
  ['sqrtf', {'link_with': ['m']}],
]

check_headers = [
  ['sys/mman.h'],
  ['fenv.h'],
  ['sys/time.h'],
  ['unistd.h'],
]

check_header_symbols = [
  ['FE_DIVBYZERO', 'fenv.h'],
]

check_compiles = []

check_compiles += [['USE_GCC_INLINE_ASM',
'''
int main () {
  asm volatile ( "\tnop\n" : : : "cc", "memory" );
  return 0;
}
''']]

check_links = []

check_links += [['TOOLCHAIN_SUPPORTS_ATTRIBUTE_CONSTRUCTOR',
'''
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
''']]

check_links += [['HAVE_FLOAT128',
'''
__float128 a = 1.0Q, b = 2.0Q; int main (void) { return a + b; }
''']]

check_links += [['HAVE_BUILTIN_CLZ',
'''
unsigned int x = 11; int main (void) { return __builtin_clz(x); }
''']]

check_links += [['HAVE_GCC_VECTOR_EXTENSIONS',
'''
unsigned int __attribute__ ((vector_size(16))) e, a, b;
int main (void) { e = a - ((b << 27) + (b >> (32 - 27))) + 1; return e[0]; }
''']]

check_thread_flags = [
  [['-pthread'], ['-pthread']],
  [['-D_REENTRANT'], ['-lpthread']],
  [['-D_REENTRANT'], ['-lroot']],
]

check_tls_keywords = ['__thread', '__declspec(thread)']

cc = meson.get_compiler('c')

pixman_version = meson.project_version()
version_arr = pixman_version.split('.')
pixman_version_major = version_arr[0].to_int()
pixman_version_minor = version_arr[1].to_int()
pixman_version_micro = version_arr[2].to_int()

conf = configuration_data()

deps = []

c_args = [
  '-DHAVE_CONFIG_H',
  '-Wno-unused-local-typedefs',
  '-fno-strict-aliasing',
  '-fvisibility=hidden',
  '-Wno-unused-const-variable',
]

link_args = []

c_args = cc.get_supported_arguments(c_args)

incbase = [include_directories('.')]

conf.set_quoted('PACKAGE', meson.project_name())

foreach check : check_sizeofs
  type = check[0]
  conf.set('SIZEOF_@0@'.format(type.to_upper()), cc.sizeof(type))
endforeach

foreach check : check_optional_deps
  name = check[0]
  opts = check.length() > 1 ? check[1] : {}
  pkg_name = opts.get('pkg', name)
  conf_prefix = opts.get('conf-prefix', 'have')

  if opts.contains('version')
    dep = dependency(pkg_name, version : opts['version'], required : false)
  else
    dep = dependency(pkg_name, required : false)
  endif

  if dep.found()
    conf.set('@0@_@1@'.format(conf_prefix, name).to_upper(), 1)
    deps += [dep]
  endif
endforeach

foreach check : check_funcs
  name = check[0]
  opts = check.length() > 1 ? check[1] : {}
  link_withs = opts.get('link_with', [])
  extra_deps = []
  found = true

  foreach link_with : link_withs
    dep = cc.find_library(link_with)
    if dep.found()
      extra_deps += dep
    else
      found = false
    endif
  endforeach

  if found
    found = cc.has_function(name, dependencies: extra_deps)
  endif

  if found
    deps += extra_deps
    conf.set('HAVE_@0@'.format(name.to_upper()), 1)
  endif
endforeach

foreach check : check_headers
  name = check[0]

  if cc.has_header(name)
    conf.set('HAVE_@0@'.format(name.to_upper().underscorify()), 1)
  endif
endforeach

foreach check : check_header_symbols
  name = check[0]
  header = check[1]

  if cc.has_header_symbol(header, name)
    conf.set('HAVE_@0@'.format(name.to_upper()), 1)
  endif
endforeach

foreach check : check_compiles
  name = check[0]
  prog = check[1]

  if cc.compiles(prog, name: name)
    conf.set(name.to_upper(), 1)
  endif
endforeach

foreach check : check_links
  name = check[0]
  prog = check[1]

  if cc.links(prog, name: name)
    conf.set(name.to_upper(), 1)
  endif
endforeach

foreach thread_flags : check_thread_flags
  if not conf.has('HAVE_PTHREADS')
    cflags = thread_flags[0]
    lflags = thread_flags[1]
    if cc.links(files('thread-test.c'), args: cflags + lflags, name: 'pthreads')
      conf.set('HAVE_PTHREADS', 1)
      c_args += cflags
      lflags += lflags
    endif
  endif
endforeach

TLS_CHECK_PROG = '''
#if defined(__MINGW32__) && !(__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
#error This MinGW version has broken __thread support
#endif
#ifdef __OpenBSD__
#error OpenBSD has broken __thread support
#endif

int @0@ test;
'''

foreach keyword : check_tls_keywords
  if not conf.has('TLS')
    if cc.compiles(TLS_CHECK_PROG.format(keyword), name: 'TLS @0@'.format(keyword))
      conf.set('TLS', keyword)
    endif
  endif
endforeach

if not conf.has('TLS')
  warning ('Pixman compiled without thread local storage support')
endif

subdir('pixman')
subdir('test')

if conf.has('HAVE_GTK')
  subdir('demos')
endif

configure_file(output: 'config.h', configuration: conf)

pkgmod.generate(libpixman,
  description: 'The pixman library (version 1)',
  version: pixman_version)
