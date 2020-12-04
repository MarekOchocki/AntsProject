cmake_minimum_required (VERSION 3.12)
project(Ants)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# add subdirectories
add_subdirectory(Utils)
add_subdirectory(SFML)
add_subdirectory(ANN)
add_subdirectory(AntsLib)

# create target
add_executable(Ants "main.cpp")

# link libraries
target_link_libraries(Ants PRIVATE Utils)
target_link_libraries(Ants PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(Ants PRIVATE ANN)
target_link_libraries(Ants PRIVATE AntsLib)

install(TARGETS Ants DESTINATION bin/)