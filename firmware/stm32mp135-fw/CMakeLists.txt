cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")
include(arm-none-eabi-gcc)


# 프로젝트 이름은 최종 출력 파일 이름으로 사용된다.
#
set(PRJ_NAME stm32mp135-fw)


project(${PRJ_NAME}
  LANGUAGES ASM C CXX
)

set(EXECUTABLE ${PRJ_NAME}.elf)


# 지정한 폴더에 있는 파일만 포함한다.
#
file(GLOB SRC_FILES CONFIGURE_DEPENDS
  src/*.cpp
  src/*.c
  src/bsp/*.c
  src/bsp/device/*.c
  src/bsp/startup/*.c
)

# 하위폴더에 있는 파일까지 포함한다.
#
file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  src/ap/*.c
  src/bsp/*.s
  src/common/*.c
  src/hw/*.c
  src/lib/ST/CMSIS/*.c
  src/lib/ST/STM32MP13xx_HAL_Driver/Src/*.c
  src/lib/ST/STM32_USB_Device_Library/Core/Src/*.c
)

# 특정 폴더를 빌드에서 제외한다.
#
set(EXCLUDE_PATHS 
)

foreach(TMP_PATH ${SRC_FILES_RECURSE}) 
  foreach(EXCLUDE_PATH ${EXCLUDE_PATHS}) 
    string(FIND ${TMP_PATH} ${EXCLUDE_PATH} RESULT) 
    if(NOT ${RESULT} EQUAL -1) 
      list(REMOVE_ITEM SRC_FILES_RECURSE ${TMP_PATH}) 
    endif() 
  endforeach(EXCLUDE_PATH) 
endforeach(TMP_PATH)


add_executable(${EXECUTABLE} 
  ${SRC_FILES}
  ${SRC_FILES_RECURSE}
)


target_include_directories(${EXECUTABLE} PRIVATE 
  src  
  src/ap
  src/ap/thread
  src/bsp
  src/bsp/device
  src/common 
  src/common/core
  src/common/hw/include 
  src/hw
  src/hw/driver
  src/hw/driver/usb
  src/hw/driver/usb/usb_cdc  
  src/hw/driver/eeprom
  src/lib

  src/lib/ST/CMSIS/Core_A/Include
  src/lib/ST/CMSIS/Device/ST/STM32MP13xx/Include
  src/lib/ST/STM32MP13xx_HAL_Driver/Inc
  src/lib/ST/STM32_USB_Device_Library/Core/Inc

  )

target_compile_definitions(${EXECUTABLE} PRIVATE
  -DUSE_HAL_DRIVER
  -DSTM32MP135Fxx
  -DCORE_CA7
  -DGPIO_AF7_LCD=0x07
  -DDDR_TYPE_DDR3_4Gb
  -DMMU_USE
  -DCACHE_USE
  )

target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-a7
  -mthumb
  # -mfpu=vfpv4-d16
  -mfpu=neon-vfpv4  
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections
  -Wstack-usage=1024

  -Wall
  -g3
  -Og
  )

target_link_options(${EXECUTABLE} PRIVATE
  # -T../src/bsp/ldscript/STM32MP135FAFX_RAM.ld
  -T../src/bsp/ldscript/STM32MP135FAFX_DDR.ld
  -mcpu=cortex-a7
  -mthumb
  # -mfpu=vfpv4-d16
  -mfpu=neon-vfpv4
  -mfloat-abi=hard
  -specs=nano.specs
  -lc
  -lm
  -lstdc++
  -lsupc++
  # -lnosys

  # -u _printf_float

  -Wl,-Map=${PRJ_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
  )

add_custom_command(TARGET ${EXECUTABLE} 
  POST_BUILD
  COMMAND ${CMAKE_SIZE_UTIL}  ${EXECUTABLE} --format=berkeley 
  )   

add_custom_command(TARGET ${EXECUTABLE} 
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
  COMMENT "Invoking: Make Binary"
  )  

 