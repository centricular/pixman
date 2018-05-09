pixman_sources = [
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

simd_sources = [
  ['USE_X86_MMX', ['pixman-mmx.c'], mmx_cflags],
  ['USE_VMX', ['pixman-vmx.c'], vmx_cflags],
  ['USE_SSE2', ['pixman-sse2.c'], sse2_cflags],
  ['USE_SSSE3', ['pixman-ssse3.c'], ssse3_cflags],
  ['USE_ARM_SIMD', ['pixman-arm-simd.c', 'pixman-arm-simd-asm.S', 'pixman-arm-simd-asm-scaled.S'], []],
  ['USE_ARM_NEON', ['pixman-arm-neon.c', 'pixman-arm-neon-asm.S', 'pixman-arm-neon-asm-bilinear.S'], []],
  ['USE_ARM_IWMMXT', ['pixman-mmx.c'], []],
  ['USE_MIPS_DSPR2', ['pixman-mips-dspr2.c', 'pixman-mips-dspr2-asm.S', 'pixman-mips-memcpy-asm.S'], []],
  ['USE_LOONGSON_MMI', ['pixman-mmx.c'], loongson_mmi_cflags],
]

simdlibs = []

foreach simd : simd_sources
  conf_flag = simd[0]
  sources = simd[1]
  cflags = simd[2]

  if conf.has(conf_flag)
    simdlibs += [static_library('simd_@0@'.format(conf_flag), sources,
      c_args: cflags + c_args,
      include_directories: incbase,
      dependencies: deps,
    )]
  endif
endforeach

incpixman = [include_directories('.')]

libpixman = library('pixman', pixman_sources,
  c_args: c_args,
  include_directories: incbase + incpixman,
  link_with: simdlibs,
  dependencies: deps)

pixman_dep = declare_dependency(link_with: libpixman,
  include_directories : incpixman,
  dependencies: deps
)
