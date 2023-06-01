project('test_system', 'cpp', version: '0.1.0')
src = ['src/main.cpp', 'src/registration_group.cpp', 'src/group_manager.cpp']
sanitazers = ['-fsanitize=address', '-fsanitize=leak', '-fsanitize=undefined', '-fsanitize=null']
    

libpq_dep = dependency('libpq')

fltk_config = find_program('fltk-config')
fltk_include_dirs = run_command(fltk_config, '--includedir', check:
true).stdout().strip().split()
fltk_cxxflags = run_command(fltk_config, '--cxxflags', check:
true).stdout().strip().split()
fltk_link_args = run_command(fltk_config, '--ldflags', '--libs', check:
true).stdout().strip().split()
fltk_dep = declare_dependency(compile_args: fltk_cxxflags,
include_directories: fltk_include_dirs,
link_args: fltk_link_args)

cc = meson.get_compiler('cpp')


if get_option('buildtype') == 'debug'
    add_project_arguments(sanitazers, language : 'cpp')
    add_project_link_arguments(sanitazers, language : 'cpp')
endif

executable('test_sys', src, dependencies: [fltk_dep, libpq_dep])
