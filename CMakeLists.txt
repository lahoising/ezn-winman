project(ezn_winman)
set(EZN_WINMAN_LIB ezn_winman)

file(
    GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**.cpp"
)

file(
    GLOB INC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/include/**.h"
)

set(EZN_WINMAN_LIB_TYPE SHARED CACHE STRING "Winman library type (e.g. SHARED, STATIC, etc)")
add_library(
    ${EZN_WINMAN_LIB} ${EZN_WINMAN_LIB_TYPE}
    ${SRC_FILES}
    ${INC_FILES}
)
target_include_directories(
    ${EZN_WINMAN_LIB} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
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