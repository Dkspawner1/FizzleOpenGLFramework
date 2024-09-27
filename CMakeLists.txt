cmake_minimum_required(VERSION 3.10)
project(FizzleFramework)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Explicitly set build directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Find packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# Find GLFW
if(WIN32)
    find_package(glfw3 REQUIRED CONFIG)
elseif(APPLE)
    find_package(glfw3 REQUIRED CONFIG)
elseif(UNIX)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
endif()

# Recursively find all .cpp files in the src directory
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add executable with all source files
add_executable(FizzleFramework ${SOURCE_FILES})

# Include directories
target_include_directories(FizzleFramework PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(FizzleFramework PRIVATE
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    GLEW::GLEW
    glm::glm
)

# Set output directory
set_target_properties(FizzleFramework PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add compile definitions for GLFW
if(UNIX AND NOT APPLE)
    target_compile_definitions(FizzleFramework PRIVATE GLFW_EXPOSE_NATIVE_X11)
endif()

