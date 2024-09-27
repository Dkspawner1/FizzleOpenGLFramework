cmake_minimum_required(VERSION 3.10)
project(FizzleFramework)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compile definitions
add_compile_definitions(GLEW_STATIC GLEW_NO_GLU)

# Set build directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Set OpenGL preference
set(OpenGL_GL_PREFERENCE GLVND)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

# Find GLFW (platform-specific)
if(WIN32 OR APPLE)
    find_package(glfw3 REQUIRED CONFIG)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
endif()

# Collect source files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    GLEW::GLEW
    glm::glm
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Add compile definitions for GLFW on Unix (non-Apple)
if(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_EXPOSE_NATIVE_X11)
endif()

# Enable warnings
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Print build type
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

