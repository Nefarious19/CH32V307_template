file(
    GLOB_RECURSE 
    HELPERS_SRCS
    *.c
    *.cpp
)

target_sources(
    ${ELF_FILE}
    PRIVATE
    ${HELPERS_SRCS}
)

target_include_directories(
    ${ELF_FILE}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)