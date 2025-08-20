# tests/CMakeLists.txt
enable_testing()

# 1️⃣ Define the test target
add_executable(tests_main
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_orbit.cpp
    # add more test files here
)

# 2️⃣ Add includes
target_include_directories(tests_main PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src    # if tests reuse internal headers
)

# 3️⃣ Link only what's needed
# GLM is header-only; use glm::glm if found via find_package in root
target_link_libraries(tests_main PRIVATE
    ${GLM_TARGET}
)

# 4️⃣ Register the test with CTest
add_test(NAME OrbitTest COMMAND tests_main)
