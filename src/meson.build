
configure_file(output: 'config.h', configuration: conf)

resources = gnome.compile_resources(
  'gt-resources',
  gt_gresource,
  install_header : true,
  export : true,
  source_dir : resource_dir,
  c_name : 'gt'
)

sources = [
  resources,
  'gt-application.h',
  'gt-application.c',
  'gt-header-bar.h',
  'gt-header-bar.c',
  'gt-window.h',
  'gt-window.c',
  'main.c',
]

executable(
  'gt', [sources],
  dependencies : [gtk_dep]
)
