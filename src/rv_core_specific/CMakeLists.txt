target_sources(
    ${ELF_FILE}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core_riscv.c
)

target_include_directories(
    ${ELF_FILE}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)