cmake_minimum_required(VERSION 3.11)

project(
  Graph
  VERSION 0.1
  DESCRIPTION "COA TP4 - Graph class")

add_executable(tp4 src/main_template.cpp)


add_compile_options(-fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

enable_testing()

#add_subdirectory(src)
add_subdirectory(test)

