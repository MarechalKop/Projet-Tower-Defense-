cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)

# You can set the name of your project here
project(MyGraphProject)

# Libraries

# ---Add GL---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
set(ALL_LIBRARIES ${OPENGL_LIBRARIES})

# ---Add GLFW---
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/glfw)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glfw)

# ---Add glad---
add_library(glad third_party/glad/src/glad.c)
include_directories(third_party/glad/include)
set(ALL_LIBRARIES ${ALL_LIBRARIES} glad)

# Link the sil library into the project
add_subdirectory(lib/sil)
set(ALL_LIBRARIES ${ALL_LIBRARIES} sil)

# Add all the source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp lib/random.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src lib)

# Link all libraries to the project
target_link_libraries(${PROJECT_NAME} PRIVATE ${ALL_LIBRARIES})

# Choose your C++ version
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Set the folder where the executable will be created
set(OUTPUT_BIN_FOLDER ${CMAKE_SOURCE_DIR}/bin)

# Configure assets header file
configure_file(help/helpers/RootDir.hpp.in help/helpers/RootDir.hpp)
include_directories(${CMAKE_BINARY_DIR}/help)
