file(
    GLOB_RECURSE
    DRIVERS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

target_sources(
    ${ELF_FILE}
    PRIVATE
    ${DRIVERS_SRCS}
)

target_include_directories(
    ${ELF_FILE}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)