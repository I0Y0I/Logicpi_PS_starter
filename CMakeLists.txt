set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER  arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

get_filename_component(CURRENT_DIR_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)
project(${CURRENT_DIR_NAME} C CXX ASM)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

add_compile_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)

add_compile_options($<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>)

add_compile_options(-Og -g)

include_directories("Application/Inc" "Drivers/CMSIS" "Drivers/CMSIS/GD/GD32F30x/Include" "Drivers/GD32F30x_standard_peripheral/Include" "Drivers/PicoKit/Inc" "Drivers/BSP/Inc")

add_definitions(-DDEBUG -DGD32F3 -DGD32F30x -DGD32F303 -DGD32F30X_HD)

file(GLOB_RECURSE SOURCES "Application/Src/*.*" "Drivers/CMSIS/GD/GD32F30x/Source/*.*" "Drivers/CMSIS/GD/GD32F30x/Source/GCC/*.*" "Drivers/GD32F30x_standard_peripheral/Source/*.*" "Drivers/PicoKit/Src/*.*" "Drivers/BSP/Src/*.*")

set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/Project/gd32f303cbt6.lds")

add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=cortex-m4 -mthumb -mthumb-interwork)
#add_link_options(-specs=nano.specs -lc -lgcc)
#add_link_options(-lc -lgcc)
add_link_options(-specs=nosys.specs)
add_link_options(-T ${LINKER_SCRIPT})

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")