project('gt', 'c',
  version : '0.0.1',
  license : 'MIT',
  default_options : ['c_std=gnu11'])

gnome = import('gnome')

gt_version = meson.project_version().split('.')
gt_major_version = gt_version[0].to_int()
gt_minor_version = gt_version[1].to_int()
gt_micro_version = gt_version[2].to_int()
if gt_version.length() == 4
  gt_nano_version = gt_version[3].to_int()
else
  gt_nano_version = 0
endif

gt_prefix = get_option('prefix')
gt_libdir = join_paths(gt_prefix, get_option('libdir'))
gt_datadir = join_paths(gt_prefix, get_option('datadir'))
gt_includedir = join_paths(gt_prefix, get_option('includedir'))

cc = meson.get_compiler('c')

conf = configuration_data()
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('PACKAGE_STRING', '@0@-@1@'.format(meson.project_name(), meson.project_version()))
conf.set_quoted('PACKAGE_DATADIR', join_paths(get_option('prefix'), get_option('datadir')))
conf.set_quoted('PACKAGE_LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))
conf.set_quoted('PACKAGE_LOCALEDIR', join_paths(get_option('prefix'), get_option('datadir'), 'locale'))
conf.set_quoted('PACKAGE_LIBEXECDIR', join_paths(get_option('prefix'), get_option('libexecdir')))

conf.set('GT_CREATED_YEAR', 2017)

conf.set('GT_MAJOR_VERSION', gt_major_version)
conf.set('GT_MINOR_VERSION', gt_minor_version)
conf.set('GT_MICRO_VERSION', gt_micro_version)

my_args = [
  '-Wpointer-arith',
  '-Wmissing-declarations',
  '-Wformat=2',
  '-Wstrict-prototypes',
  '-Wmissing-prototypes',
  '-Wnested-externs',
  '-Wbad-function-cast',
  '-Wold-style-definition',
  '-Wdeclaration-after-statement',
  '-Wunused',
  '-Wuninitialized',
  '-Wshadow',
  '-Wmissing-noreturn',
  '-Wmissing-format-attribute',
  '-Wredundant-decls',
  '-Wlogical-op',
  '-Werror=implicit',
  '-Werror=nonnull',
  '-Werror=init-self',
  '-Werror=main',
  '-Werror=missing-braces',
  '-Werror=sequence-point',
  '-Werror=return-type',
  '-Werror=trigraphs',
  '-Werror=array-bounds',
  '-Werror=write-strings',
  '-Werror=address',
  '-Werror=int-to-pointer-cast',
  '-Werror=pointer-to-int-cast',
  '-fno-strict-aliasing',
  '-Wno-int-conversion',
]

add_global_arguments(my_args, language : 'c')

gtk_dep = dependency('gtk+-3.0')

configure_file(
  output : 'config.h',
  configuration : conf
)

resource_dir = join_paths(meson.source_root(), 'data')
gt_gresource = files(join_paths(resource_dir, 'gt.gresource.xml'))

subdir('data')
subdir('src')
