project('gtk-test', 'c',
  version : '0.0.1',
  license : 'MIT',
  default_options : ['c_std=gnu11'])

gtk_test_version = meson.project_version().split('.')
gtk_test_major_version = gtk_test_version[0].to_int()
gtk_test_minor_version = gtk_test_version[1].to_int()
gtk_test_micro_version = gtk_test_version[2].to_int()
if gtk_test_version.length() == 4
  gtk_test_nano_version = gtk_test_version[3].to_int()
else
  gtk_test_nano_version = 0
endif

gtk_test_prefix = get_option('prefix')
gtk_test_libdir = join_paths(gtk_test_prefix, get_option('libdir'))
gtk_test_datadir = join_paths(gtk_test_prefix, get_option('datadir'))
gtk_test_includedir = join_paths(gtk_test_prefix, get_option('includedir'))

cc = meson.get_compiler('c')

conf = configuration_data()
conf.set_quoted('PACKAGE_NAME', meson.project_name())
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('PACKAGE_STRING', '@0@-@1@'.format(meson.project_name(), meson.project_version()))
conf.set_quoted('PACKAGE_DATADIR', join_paths(get_option('prefix'), get_option('datadir')))
conf.set_quoted('PACKAGE_LIBDIR', join_paths(get_option('prefix'), get_option('libdir')))
conf.set_quoted('PACKAGE_LOCALEDIR', join_paths(get_option('prefix'), get_option('datadir'), 'locale'))
conf.set_quoted('PACKAGE_LIBEXECDIR', join_paths(get_option('prefix'), get_option('libexecdir')))

conf.set('GTK_TEST_MAJOR_VERSION', gtk_test_major_version)
conf.set('GTK_TEST_MINOR_VERSION', gtk_test_minor_version)
conf.set('GTK_TEST_MICRO_VERSION', gtk_test_micro_version)

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

subdir('src')
