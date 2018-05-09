simd_mod = import('unstable-simd')

sources = [
  'pixman.c',
  'pixman-access.c',
  'pixman-access-accessors.c',
  'pixman-bits-image.c',
  'pixman-combine32.c',
  'pixman-combine-float.c',
  'pixman-conical-gradient.c',
  'pixman-filter.c',
  'pixman-x86.c',
  'pixman-mips.c',
  'pixman-arm.c',
  'pixman-ppc.c',
  'pixman-edge.c',
  'pixman-edge-accessors.c',
  'pixman-fast-path.c',
  'pixman-glyph.c',
  'pixman-general.c',
  'pixman-gradient-walker.c',
  'pixman-image.c',
  'pixman-implementation.c',
  'pixman-linear-gradient.c',
  'pixman-matrix.c',
  'pixman-noop.c',
  'pixman-radial-gradient.c',
  'pixman-region16.c',
  'pixman-region32.c',
  'pixman-solid-fill.c',
  'pixman-timer.c',
  'pixman-trap.c',
  'pixman-utils.c',
]

headers = [
  'pixman.h',
  'pixman-accessor.h',
  'pixman-combine32.h',
  'pixman-compiler.h',
  'pixman-edge-imp.h',
  'pixman-inlines.h',
  'pixman-private.h',
]

verconf = configuration_data()
verconf.set('PIXMAN_VERSION_MAJOR', pixman_version_major)
verconf.set('PIXMAN_VERSION_MINOR', pixman_version_minor)
verconf.set('PIXMAN_VERSION_MICRO', pixman_version_micro)

configure_file(
  input: 'pixman-version.h.in',
  output: 'pixman-version.h',
  configuration: verconf
)

# TODO: add support for other architectures SIMDs in meson

ret = simd_mod.check('pixman-simds',
  mmx: 'pixman-mmx.c',
  sse2: 'pixman-sse2.c',
  ssse3: 'pixman-ssse3.c',
  compiler: cc,
  include_directories: incbase,
  c_args: c_args,
)

simdlibs = ret[0]
simdconf = ret[1]

if simdconf.get('HAVE_MMX') == '1'
  conf.set('USE_X86_MMX', 1)
endif

if simdconf.get('HAVE_SSE2') == '1'
  conf.set('USE_SSE2', 1)
endif

if simdconf.get('HAVE_SSSE3') == '1'
  conf.set('USE_SSSE3', 1)
endif

incpixman = [include_directories('.')]

libpixman = library('pixman', sources,
  c_args: c_args,
  include_directories: incbase + incpixman,
  link_with: simdlibs,
  dependencies: deps)

pixman_dep = declare_dependency(link_with: libpixman,
  include_directories : incpixman,
  dependencies: deps
)
