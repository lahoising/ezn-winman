cmake_minimum_required(VERSION 3.10)
project(ezn_winman)
set(EZN_WINMAN_LIB ezn_winman)

file(
    GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)

set(EZN_WINMAN_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(
    GLOB INC_FILES
    "${EZN_WINMAN_INC_DIR}/**.h"
)
set(EZN_WINMAN_INCLUDE_DIRECTORIES "${EZN_WINMAN_INC_DIR}")

set(EZN_WINMAN_LIB_TYPE SHARED CACHE STRING "Winman library type (e.g. SHARED, STATIC, etc)")
add_library(
    ${EZN_WINMAN_LIB} ${EZN_WINMAN_LIB_TYPE}
    ${SRC_FILES}
    ${INC_FILES}
)
target_include_directories(
    ${EZN_WINMAN_LIB} PUBLIC
    "${EZN_WINMAN_INCLUDE_DIRECTORIES}"
)

set(EXTERNAL_INC "${CMAKE_CURRENT_SOURCE_DIR}/external")

# opengl
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_link_libraries(${EZN_WINMAN_LIB} OpenGL::GL)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("${EXTERNAL_INC}/glfw")
target_link_libraries(${EZN_WINMAN_LIB} glfw)

set(EZN_WINMAN_INCLUDE_DIRECTORIES "${EZN_WINMAN_INCLUDE_DIRECTORIES}" PARENT_SCOPE)

###
# examples
###
set(EZN_WINMANN_BUILD_EXAMPLES ON CACHE BOOL "Build winman examples")
if(${EZN_WINMANN_BUILD_EXAMPLES})
    file(GLOB example_files "${CMAKE_CURRENT_SOURCE_DIR}/examples/**.cpp")
    foreach(f ${example_files})
        get_filename_component(ex ${f} NAME_WE)
        add_executable(${ex} ${f})
        target_link_libraries(${ex} ${EZN_WINMAN_LIB})
    endforeach()
endif()