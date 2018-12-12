project('pixman', 'c',
  version : '0.35.1',
  meson_version : '>= 0.47.0',
  default_options: [ 'buildtype=debugoptimized'],
)

pkgmod = import('pkgconfig')

cc = meson.get_compiler('c')

conf = configuration_data()

check_sizeofs = [
  ['long'],
]

check_optional_deps = [
  ['gtk', {'pkg': 'gtk+-2.0', 'version': '>= 2.16', 'option': 'gtk2'}],
  ['libpng', {'fallback': ['libpng', 'libpng_dep'], 'option': 'png'}],
]

if cc.get_id() != 'msvc'
  check_optional_deps += [['openmp', {'conf-prefix': 'use'}]]
endif

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

if cc.get_id() == 'sun'
  mmx_cflags = ['-xarch=sse']
  sse2_cflags = ['-xarch=sse2']
  ssse3_cflags = ['-mssse3', '-Winline']
elif cc.get_id() == 'msvc'
  mmx_cflags = ['/w14710', '/w14714', '/wd4244']
  mmx_cflags = []
  sse2_cflags = []
  ssse3_cflags = []
else
  mmx_cflags = ['-mmmx', '-Winline']
  sse2_cflags = ['-msse2', '-Winline']
  ssse3_cflags = ['-mssse3', '-Winline']
endif
vmx_cflags = ['-maltivec', '-mabi=altivec'] # FIXME grep Apple ?
arm_simd_cflags = ['-x assembler-with-cpp']
arm_neon_cflags = ['-x assembler-with-cpp']
arm_iwmmxt_cflags = ['-flax-vector-conversions', '-Winline', '-march=iwmmxt']
mips_dspr2_cflags = ['-mdspr2']
loongson_mmi_cflags = ['-march=loongson2f']

check_compiles = []

if cc.get_id() == 'msvc'
  if host_machine.cpu_family() == 'x86'
    conf.set('USE_X86_MMX', 1)
    conf.set('USE_SSE2', 1)
    conf.set('USE_SSSE3', 1)
    message('Enabling MMX, SSE2, SSSE3')
  elif host_machine.cpu_family() == 'x86_64'
    conf.set('USE_SSE2', 1)
    conf.set('USE_SSSE3', 1)
    message('Enabling SSE2, SSSE3')
  endif
else
  # None of these compiler checks work on MSVC
  check_compiles += [
    ['USE_X86_MMX', files('meson-cc-tests/mmx-test.c'), {'c_args': mmx_cflags}],
    ['USE_SSE2', files('meson-cc-tests/sse2-test.c'), {'c_args': sse2_cflags}],
    ['USE_SSSE3', files('meson-cc-tests/ssse3-test.c'), {'c_args': ssse3_cflags}],
    ['USE_VMX', files('meson-cc-tests/vmx-test.c'), {'c_args': vmx_cflags}],
    ['USE_ARM_IWMMXT', files('meson-cc-tests/arm-iwmmxt-test.c'), {'c_args': arm_iwmmxt_cflags}],
    ['USE_MIPS_DSPR2', files('meson-cc-tests/mips-dspr2-test.c'), {'c_args': mips_dspr2_cflags}],
    ['USE_LOONGSON_MMI', files('meson-cc-tests/loongson-mmi-test.c'), {'c_args': loongson_mmi_cflags + ['-I' + meson.current_source_dir()]}],
    ['USE_GCC_INLINE_ASM', files('meson-cc-tests/gcc-inline-asm-test.c')],
    ['USE_ARM_SIMD', files('meson-cc-tests/arm-simd-test.S'), {'c_args': arm_simd_cflags}],
    ['USE_ARM_NEON', files('meson-cc-tests/arm-neon-test.S'), {'c_args': arm_neon_cflags}],
  ]
endif

check_links = [
  ['TOOLCHAIN_SUPPORTS_ATTRIBUTE_CONSTRUCTOR', files('meson-cc-tests/attribute-constructor-test.c')],
  ['HAVE_FLOAT128', files('meson-cc-tests/float128-test.c')],
  ['HAVE_BUILTIN_CLZ', files('meson-cc-tests/builtin-clz-test.c')],
  ['HAVE_GCC_VECTOR_EXTENSIONS', files('meson-cc-tests/gcc-vector-extensions.c')],
]

check_thread_flags = [
  [['-pthread'], ['-pthread']],
  [['-D_REENTRANT'], ['-lpthread']],
  [['-D_REENTRANT'], ['-lroot']],
]

check_tls_keywords = ['__thread', '__declspec(thread)']

pixman_version = meson.project_version()
version_arr = pixman_version.split('.')
pixman_version_major = version_arr[0].to_int()
pixman_version_minor = version_arr[1].to_int()
pixman_version_micro = version_arr[2].to_int()

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
  name = check.get(0)
  opts = check.get(1, {})
  pkg_name = opts.get('pkg', name)
  conf_prefix = opts.get('conf-prefix', 'have')
  if opts.has_key('option')
    req = get_option(opts['option'])
  else
    req = false
  endif

  if opts.has_key('version')
    dep = dependency(pkg_name, version : opts['version'], required : req)
  elif opts.has_key('fallback')
    dep = dependency(pkg_name, fallback : opts['fallback'], required : req)
  else
    dep = dependency(pkg_name, required : req)
  endif

  if dep.found()
    conf.set('@0@_@1@'.format(conf_prefix, name).to_upper(), 1)
    deps += [dep]
  endif
endforeach

foreach check : check_funcs
  name = check.get(0)
  opts = check.get(1, {})
  link_withs = opts.get('link_with', [])
  extra_deps = []
  found = true

  # First try without linking

  found = cc.has_function(name)

  if not found and link_withs.length() > 0
    found = true

    foreach link_with : link_withs
      dep = cc.find_library(link_with, required: false)
      if dep.found()
        extra_deps += dep
      else
        found = false
      endif
    endforeach

    if found
      found = cc.has_function(name, dependencies: extra_deps)
    endif
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
  name = check.get(0)
  prog = check.get(1)
  opts = check.get(2, {})
  cflags = opts.get('c_args', [])

  if cc.compiles(prog, name: name, args: cflags)
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
    if cc.links(files('meson-cc-tests/thread-test.c'), args: cflags + lflags, name: 'pthreads')
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
  subdirs: ['pixman-1'],
  version: pixman_version)
