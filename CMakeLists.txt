cmake_minimum_required(VERSION 3.16)

project(Reyes)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_UNITY_BUILD ON)

if (MSVC)
    add_compile_options(/GX /w)
else ()
    add_compile_options(-Wno-int-to-pointer-cast)
endif ()

if (WIN32)
    add_compile_definitions(REY_WINDOWS)
endif ()

OPTION(DIST "Use distribution mode")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(REY_DEBUG)
else ()
    if (DIST)
        add_compile_definitions(REY_DIST)
    else ()
        add_compile_definitions(REY_RELEASE)
    endif ()
endif ()

find_package(OpenGL REQUIRED)
file(GLOB_RECURSE Reyes_SRC Reyes/src/*.h Reyes/src/*.cpp Reyes/vendor/stb/*.cpp Reyes/vendor/stb/*.h Reyes/vendor/glm/glm/*.hpp Reyes/vendor/glm/glm/*.inl)
add_library(Reyes STATIC Reyes/src/Reyes/Core/Core.h ${Reyes_SRC})
target_precompile_headers(Reyes PRIVATE Reyes/src/pch)

include_directories(Reyes/src Reyes/vendor Reyes/vendor/glm Reyes/vendor/spdlog/include Reyes/vendor/stb)
target_include_directories(Reyes PRIVATE Reyes/vendor/glfw/include Reyes/vendor/glad/include Reyes/vendor/imgui Reyes/vendor/freetype/include)

include_directories(Reyes/vendor/glfw/include Reyes/vendor/glad/include Reyes/vendor/stb)

if (WIN32)
    target_compile_definitions(Reyes PRIVATE REY_EXPORT_LIBRARY)
endif ()

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_BUILD_INSTALL OFF CACHE BOOL "")

add_subdirectory(Reyes/vendor/glfw)
add_subdirectory(Reyes/vendor/glad)
add_subdirectory(Reyes/vendor/imgui)
add_subdirectory(Reyes/vendor/freetype)
target_link_libraries(Reyes glfw glad imgui freetype OpenGL::GL)

file(GLOB_RECURSE Sandbox_SRC Sandbox/src/*.h Sanbox/src/*.cpp)
add_executable(Sandbox Sandbox/src/SandboxApp.cpp)
target_link_libraries(Sandbox Reyes imgui)

# file(GLOB_RECURSE Button_SRC Button/src/*.h Button/src/*.cpp)
# add_executable(Button ${Button_SRC})
# target_link_libraries(Button glfw glad)