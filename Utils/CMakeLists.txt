
cmake_minimum_required (VERSION 3.12)
project(Utils)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

file(GLOB Utils_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/Utils/*")
file(GLOB_RECURSE UTILS_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*")

add_library(Utils SHARED ${Utils_HEADERS} ${UTILS_SOURCES})

set_target_properties(Utils PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Utils PUBLIC include)

install(DIRECTORY include DESTINATION .)
install(TARGETS Utils DESTINATION bin/)