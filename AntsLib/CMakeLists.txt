cmake_minimum_required (VERSION 3.12)
project(AntsLib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

file(GLOB_RECURSE AntsLib_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/*")
file(GLOB_RECURSE AntsLib_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*")

add_library(AntsLib SHARED ${AntsLib_HEADERS} ${AntsLib_SOURCES} )
target_link_libraries(AntsLib PRIVATE Utils)
target_link_libraries(AntsLib PRIVATE ANN)
target_link_libraries(AntsLib PRIVATE sfml-graphics sfml-window sfml-system)

set_target_properties(AntsLib PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(AntsLib PUBLIC include)

install(DIRECTORY include DESTINATION .)
install(TARGETS AntsLib DESTINATION bin/)