BSP_ROOT ?= /home/rx-ted/project/rtt/art-pi/projects/1lcd_8080
RTT_ROOT ?= /home/rx-ted/project/rtt/rt-thread

CROSS_COMPILE ?=/usr/bin/arm-none-eabi-

CFLAGS := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g
AFLAGS := -c -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2
LFLAGS := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=build/rtthread.map,-cref,-u,Reset_Handler -T board/linker_scripts/STM32H750XBHx/link.lds
CXXFLAGS := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g
EXTERN_LIB := -lc -lm 

CPPPATHS :=-I$(BSP_ROOT)/applications \
	-I$(RTT_ROOT)/components/libc/compilers/newlib \
	-I$(RTT_ROOT)/components/libc/compilers/common/include \
	-I$(RTT_ROOT)/components/libc/cplusplus \
	-I$(RTT_ROOT)/components/libc/cplusplus/cpp11/gcc \
	-I$(RTT_ROOT)/components/drivers/include \
	-I$(RTT_ROOT)/components/drivers/spi \
	-I$(RTT_ROOT)/components/drivers/spi/sfud/inc \
	-I$(BSP_ROOT)/board \
	-I$(BSP_ROOT)/board/port \
	-I$(BSP_ROOT)/board/CubeMX_Config/Core/Inc \
	-I"$(RTT_ROOT)/../art-pi/libraries/drivers", \
	-I"$(RTT_ROOT)/../art-pi/libraries/drivers/include" \
	-I"$(RTT_ROOT)/../art-pi/libraries/drivers/include/config" \
	-I$(RTT_ROOT)/components/fal/inc \
	-I$(RTT_ROOT)/components/dfs/dfs_v1/include \
	-I$(RTT_ROOT)/components/dfs/dfs_v1/filesystems/romfs \
	-I$(RTT_ROOT)/components/dfs/dfs_v1/filesystems/devfs \
	-I$(RTT_ROOT)/components/finsh \
	-I$(BSP_ROOT) \
	-I$(RTT_ROOT)/include \
	-I$(RTT_ROOT)/components/drivers/ktime \
	-I$(RTT_ROOT)/components/drivers/ktime/inc \
	-I$(RTT_ROOT)/libcpu/arm/common \
	-I$(RTT_ROOT)/libcpu/arm/cortex-m7 \
	-I"$(RTT_ROOT)/../art-pi/libraries/samples" \
	-I$(RTT_ROOT)/components/libc/posix/ipc \
	-I$(RTT_ROOT)/components/libc/posix/delay \
	-I$(RTT_ROOT)/components/libc/posix/pthreads \
	-I$(RTT_ROOT)/components/libc/posix/io/epoll \
	-I$(RTT_ROOT)/components/libc/posix/io/eventfd \
	-I$(RTT_ROOT)/components/libc/posix/io/stdio \
	-I$(RTT_ROOT)/components/libc/posix/io/poll \
	-I"$(RTT_ROOT)/../art-pi/libraries/STM32H7xx_HAL/STM32H7xx_HAL_Driver/Inc" \
	-I"$(RTT_ROOT)/../art-pi/libraries/STM32H7xx_HAL/CMSIS/Device/ST/STM32H7xx/Include" \
	-I"$(RTT_ROOT)/../art-pi/libraries/STM32H7xx_HAL/CMSIS/Include"

DEFINES := -DRT_USING_LIBC -DRT_USING_NEWLIBC -DSTM32H750xx -DUSE_HAL_DRIVER -D_POSIX_C_SOURCE=1 -D__RTTHREAD__
