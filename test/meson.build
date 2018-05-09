tests = [
  'oob-test.c',
  'infinite-loop.c',
  'trap-crasher.c',
  'fence-image-self-test.c',
  'region-translate-test.c',
  'fetch-test.c',
  'a1-trap-test.c',
  'prng-test.c',
  'radial-invalid.c',
  'pdf-op-test.c',
  'region-test.c',
  'combiner-test.c',
  'scaling-crash-test.c',
  'alpha-loop.c',
  'scaling-helpers-test.c',
  'thread-test.c',
  'rotate-test.c',
  'alphamap.c',
  'gradient-crash-test.c',
  'pixel-test.c',
  'matrix-test.c',
  'filter-reduction-test.c',
  'composite-traps-test.c',
  'region-contains-test.c',
  'glyph-test.c',
  'solid-test.c',
  'stress-test.c',
  'cover-test.c',
  'blitters-test.c',
  'affine-test.c',
  'scaling-test.c',
  'composite.c',
  'tolerance-test.c',
]

sources = [
  'utils.c',
  'utils-prng.c',
]

libtestutils = static_library('test-utils', sources,
  include_directories: incbase + incpixman,
  dependencies: deps,
  link_with: [libpixman],
  c_args: c_args)

foreach fname : tests
  test_name = fname.split('.')[0].underscorify()
  exe = executable(test_name, fname,
    include_directories: incbase + incpixman,
    c_args: c_args,
    dependencies: deps,
    link_with: [libpixman, libtestutils]
  )

  test(test_name, exe)
endforeach
