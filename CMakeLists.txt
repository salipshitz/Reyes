cmake_minimum_required(VERSION 3.16)

project(Reyes)

set(CMAKE_CXX_STANDARD 17)

include(GenerateExportHeader)

file(GLOB_RECURSE Reyes_SRC Reyes/src/*.h Reyes/src/*.cpp)
add_library(Reyes SHARED ${Reyes_SRC})
target_precompile_headers(Reyes PRIVATE Reyes/src/reypch.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR} Reyes/src Reyes/vendor/spdlog/include)

generate_export_header(Reyes
        BASE_NAME Reyes
        EXPORT_MACRO_NAME REYES_API
        EXPORT_FILE_NAME reyes_exports.h
        STATIC_DEFINE SHARED_EXPORTS_BUILT_AS_STATIC
)

file(GLOB Sandbox_SRC Sandbox/src/*.h Sanbox/src/*.cpp)
add_executable(Sandbox Sandbox/src/SandboxApp.cpp)
target_link_libraries(Sandbox Reyes)
