project(
  'gt', 'c',
  version: '0.0.1',
  license: 'MIT',
  default_options: [
    'buildtype=debugoptimized',
    'c_std=gnu11',
    'warning_level=1'
  ],
  meson_version: '>= 0.38.1'
)

gt_version = meson.project_version()
version_array = gt_version.split('.')
gt_major_version = version_array[0].to_int()
gt_minor_version = version_array[1].to_int()
gt_micro_version = version_array[2].to_int()

gt_prefix = get_option('prefix')
gt_datadir = join_paths(gt_prefix, get_option('datadir'))
gt_includedir = join_paths(gt_prefix, get_option('includedir'))
gt_libdir = join_paths(gt_prefix, get_option('libdir'))

cc = meson.get_compiler('c')

conf = configuration_data()
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('PACKAGE_VERSION', gt_version)
conf.set_quoted('PACKAGE_STRING', '@0@-@1@'.format(meson.project_name(), gt_version))
conf.set_quoted('PACKAGE_DATADIR', join_paths(get_option('prefix'), get_option('datadir')))
conf.set_quoted('PACKAGE_LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))

conf.set('GT_CREATED_YEAR', 2017)

conf.set('GT_MAJOR_VERSION', gt_major_version)
conf.set('GT_MINOR_VERSION', gt_minor_version)
conf.set('GT_MICRO_VERSION', gt_micro_version)

# Compiler flags
test_cflags = [
  '-ffast-math',
  '-fno-strict-aliasing',
  '-Wcast-align',
  '-Wdeclaration-after-statement',
  '-Werror=address',
  '-Werror=array-bounds',
  '-Werror=implicit',
  '-Werror=init-self',
  '-Werror=int-to-pointer-cast',
  '-Werror=main',
  '-Werror=missing-braces',
  '-Werror=nonnull',
  '-Werror=pointer-to-int-cast',
  '-Werror=return-type',
  '-Werror=sequence-point',
  '-Werror=trigraphs',
  '-Werror=write-strings',
  '-Wformat=2',
  '-Wlogical-op',
  '-Wmissing-declarations',
  '-Wmissing-format-attribute',
  '-Wmissing-noreturn',
  '-Wmissing-prototypes',
  '-Wnested-externs',
  '-Wno-int-conversion',
  '-Wno-unused-local-typedefs',
  '-Wold-style-definition',
  '-Wpointer-arith',
  '-Wredundant-decls',
  '-Wshadow',
  '-Wstrict-prototypes',
  '-Wuninitialized',
  '-Wunused'
]

common_flags = []
foreach cflag: test_cflags
  if cc.has_argument(cflag)
    common_flags += [cflag]
  endif
endforeach

add_global_arguments(common_flags, language: 'c')

gtk_dep = dependency('gtk+-3.0')
libpeas_dep = dependency('libpeas-1.0')
libpeas_gtk_dep = dependency('libpeas-gtk-1.0')

configure_file(
  output: 'config.h',
  configuration: conf
)

gnome = import('gnome')

top_inc = include_directories('.')

subdir('data')
subdir('src')
