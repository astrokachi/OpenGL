cmake_minimum_required(VERSION 3.10.0)
project(solar_system VERSION 0.1.0 LANGUAGES C CXX)

add_executable(solar_system src/main.cpp)

include(CTest)
enable_testing()    

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW_INCLUDE_DIRS)

include_directories(${GLFW_INCLUDE_DIRS})

target_link_libraries(solar_system ${GLFW_LIBRARIES} GL GLEW)

