cmake_minimum_required(VERSION 3.11)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(test_gnt test.cpp test_gnt.cpp)
target_compile_features(test_gnt PRIVATE cxx_std_17)  
if (WIN32)
  target_compile_options(test_gnt PRIVATE /WX /W4)
else()
  target_compile_options(test_gnt PRIVATE -Wall)  
endif()
target_include_directories(test_gnt PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test_gnt PRIVATE Catch2::Catch2)

