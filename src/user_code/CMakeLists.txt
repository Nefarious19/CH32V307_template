file(GLOB_RECURSE USER_CODE_SRCS *.c *.cpp)

target_sources(
    ${ELF_FILE}
    PRIVATE ${USER_CODE_SRCS}
)

target_include_directories(
    ${ELF_FILE}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)