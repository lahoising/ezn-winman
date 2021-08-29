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