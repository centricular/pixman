demos = [
  'clip-test.c',
  'clip-in.c',
  'composite-test.c',
  'gradient-test.c',
  'radial-test.c',
  'linear-gradient.c',
  'conical-test.c',
  'alpha-test.c',
  'screen-test.c',
  'convolution-test.c',
  'trap-test.c',
  'tri-test.c',
  'quad2quad.c',
  'checkerboard.c',
  'srgb-trap-test.c',
  'srgb-test.c',
  'scale.c',
]

sources = [
  'gtk-utils.c',
  'gtk-utils.h',
  '../test/utils.c',
  '../test/utils.h',
  '../test/utils-prng.c',
]

libdemoutils = static_library('test-utils', sources,
  include_directories: incbase + incpixman,
  dependencies: deps,
  link_with: [libpixman],
  c_args: c_args)

foreach fname : demos
  demo_name = fname.split('.')[0].underscorify()
  exe = executable(demo_name, fname,
    include_directories: incbase + incpixman,
    c_args: c_args,
    dependencies: deps,
    link_with: [libpixman, libdemoutils]
  )
endforeach
