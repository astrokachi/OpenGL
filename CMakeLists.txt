cmake_minimum_required(VERSION 3.15)
project(solar_system VERSION 0.1.0 LANGUAGES C CXX)

# Global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

# Option: prefer system packages, but fall back to fetching
option(USE_SYSTEM_DEPS "Use system-installed packages instead of fetching" ON)

# OpenGL (portable imported target)
find_package(OpenGL REQUIRED)

include(FetchContent)

# GLFW: system or FetchContent
set(GLFW_TARGET glfw)
if(USE_SYSTEM_DEPS)
  # Try config-mode first (vcpkg, Conan, brew)
  find_package(glfw3 CONFIG QUIET)
  if(TARGET glfw)
    set(GLFW_TARGET glfw)
  elseif(TARGET glfw3)
    set(GLFW_TARGET glfw3)
  else()
    # Fallback to fetching if not found
    set(USE_SYSTEM_DEPS OFF)
  endif()
endif()

if(NOT USE_SYSTEM_DEPS)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
  set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
  )
  FetchContent_MakeAvailable(glfw)
  set(GLFW_TARGET glfw)
endif()

# GLM: header-only — system or FetchContent
set(GLM_TARGET glm::glm)
if(USE_SYSTEM_DEPS)
  find_package(glm CONFIG QUIET)
  if(NOT TARGET glm::glm)
    # Fallback to fetching if not found
    set(USE_SYSTEM_DEPS OFF)
  endif()
endif()

if(NOT USE_SYSTEM_DEPS)
  FetchContent_Declare(glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
  )
  FetchContent_MakeAvailable(glm)
  # Provides glm::glm (header-only)
endif()

# Main executable (sources added in src/)
add_executable(solar_system)

# Include dirs common to app
target_include_directories(solar_system PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

# Link libraries (portable targets)
target_link_libraries(solar_system PRIVATE
  OpenGL::GL
  ${GLFW_TARGET}
  ${GLM_TARGET}
)

message(STATUS "GLM_TARGET = ${GLM_TARGET}")
if(TARGET ${GLM_TARGET})
    message(STATUS "GLM target exists!")
else()
    message(FATAL_ERROR "GLM target '${GLM_TARGET}' does not exist before adding tests.")
endif()

# Subdirectories
add_subdirectory(src)
add_subdirectory(tests)

# Packaging (optional)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

file(COPY ${CMAKE_SOURCE_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
