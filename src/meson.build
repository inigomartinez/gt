data_dir = join_paths(meson.source_root(), 'data')

resources = gnome.compile_resources(
  'gt-resources',
  join_paths(data_dir, 'gt.gresource.xml'),
  install_header: true,
  export: true,
  source_dir: data_dir,
  c_name: 'gt'
)

sources = [
  resources,
  'gt-application.h',
  'gt-application.c',
  'gt-header-bar.h',
  'gt-header-bar.c',
  'gt-preferences.h',
  'gt-preferences.c',
  'gt-window.h',
  'gt-window.c',
  'main.c',
]

executable(
  'gt',
  sources,
  include_directories: top_inc,
  dependencies: [
    gtk_dep,
    libpeas_dep,
    libpeas_gtk_dep
  ],
  install: true
)
