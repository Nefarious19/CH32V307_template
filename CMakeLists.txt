cmake_minimum_required(VERSION 3.10)

include(riscv_toolchain.cmake)

project(
    ch32v307_template
    VERSION 1.0
    LANGUAGES C ASM
)

set(TARGET_PROCESSOR_NAME           CH32V307VCT6)
set(TARGET_LINKER_FILE_DIRECTORY    ${CMAKE_CURRENT_SOURCE_DIR}/src/linker_file)
set(TARGET_LIBS
    freertos_kernel
    c
    m
    nosys
)

set(TARGET_INCLUDES
    ${RISCV_COMPILER_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/freertos_helpers
)

set(TARGET_LINK_DIRECTORIES
)

set(TARGET_COMPILE_DEFINITIONS
    "asm=__asm"
)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG       "-msave-restore -O0 -g -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG     "-msave-restore -O0 -g -ggdb")
set(CMAKE_ASM_FLAGS_DEBUG     "-msave-restore -O0 -g -ggdb")

set(CMAKE_C_FLAGS_RELEASE     "-msave-restore -Os -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE   "-msave-restore -Os -g -ggdb")
set(CMAKE_ASM_FLAGS_RELEASE   "-msave-restore -Os -g -ggdb")

set(CMAKE_C_FLAGS             "-march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized")
set(CMAKE_CXX_FLAGS           "-march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -fabi-version=0")
set(CMAKE_ASM_FLAGS           "-march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS    "-L\"${TARGET_LINKER_FILE_DIRECTORY}\" -T Link.ld -nostartfiles -Xlinker --gc-sections -Wl,-Map,\"${TARGET_PROCESSOR_NAME}.map\" -Wl,--print-memory-usage -specs=nano.specs -specs=nosys.specs")

# FreeRTOS part
set(FREERTOS_RISCV_EXTENSION    "WCH_RISC_V4A_FPU")
set(FREERTOS_PORT               "GCC_RISC_V_WCH_RISC_V4A_FPU"   CACHE STRING "")
set(FREERTOS_HEAP               "4"                             CACHE STRING "")

add_library(freertos_config INTERFACE)
target_include_directories(freertos_config
    SYSTEM INTERFACE
    ${TARGET_INCLUDES}
)

add_subdirectory(freertos)

set(ELF_FILE  ${PROJECT_NAME}.elf)
set(HEX_FILE  ${PROJECT_NAME}.hex)
set(BIN_FILE  ${PROJECT_NAME}.bin)
set(PRNT_SIZE ${PROJECT_NAME}_print_size)

add_executable(${ELF_FILE})

target_link_directories(
    ${ELF_FILE}
    PUBLIC
    ${TARGET_LINK_DIRECTORIES}
)

target_link_libraries(
    ${ELF_FILE}
    PUBLIC
    ${TARGET_LIBS}
)

add_custom_target(
    ${PRNT_SIZE}
    ALL
    DEPENDS ${ELF_FILE}
    COMMAND ${RISCV_SIZE} --format=sysv ${ELF_FILE}
    COMMENT "Print ${ELF_FILE} file size"
)

add_custom_target(
    ${HEX_FILE}
    ALL
    DEPENDS ${ELF_FILE}
    COMMAND ${RISCV_OBJCOPY} -O ihex ${ELF_FILE} ${HEX_FILE}
    COMMENT "Produce HEX file"
)

add_custom_target(
    ${BIN_FILE}
    ALL
    DEPENDS ${ELF_FILE}
    COMMAND ${RISCV_OBJCOPY} -O binary ${ELF_FILE} ${BIN_FILE}
    COMMENT "Produce BIN file"
)

add_custom_target(
    flash_mcu
    DEPENDS ${ELF_FILE}
    COMMAND ${RISCV_OPENOCD_PATH}/openocd -f ${RISCV_OPENOCD_PATH}/wch-riscv.cfg -c "program ${CMAKE_CURRENT_BINARY_DIR}/${ELF_FILE} verify reset exit"
)

add_subdirectory(src)
