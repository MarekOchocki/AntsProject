cmake_minimum_required (VERSION 3.12)
project(ANN)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

file(GLOB_RECURSE ANN_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/*")
file(GLOB_RECURSE ANN_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} "src/*")

add_library(ANN SHARED ${ANN_HEADERS} ${ANN_SOURCES} "include/ANN/Neurons/SigmoidNeuron.hpp" "src/Neurons/SigmoidNeuron.cpp")
target_link_libraries(ANN PRIVATE Utils)

set_target_properties(ANN PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(ANN PUBLIC include)

install(DIRECTORY include DESTINATION .)
install(TARGETS ANN DESTINATION bin/)