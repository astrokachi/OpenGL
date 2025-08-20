# Add sources with context-safe paths
target_sources(solar_system PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/glad.c
  ${CMAKE_CURRENT_SOURCE_DIR}/Camera.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Shader.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Sphere.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/CelestialBody.cpp
)

# If headers live here too
target_include_directories(solar_system PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)
