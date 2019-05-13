cmake_minimum_required(VERSION 3.14)
project(ews_cpp_poc)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_compile_definitions(EWS_HAS_VARIADIC_TEMPLATES)

include_directories(include)
include_directories(include/ews)
include_directories(include/ews/rapidxml)

add_executable(ews_cpp_poc main.cpp)
target_link_libraries(ews_cpp_poc ${CONAN_LIBS})
