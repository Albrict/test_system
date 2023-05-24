project('test_system', 'cpp', version: '0.1.0')
src = ['src/main.cpp']


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

executable('hellofltk', src, dependencies: [fltk_dep])
