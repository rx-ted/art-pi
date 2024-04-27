import os
from config.allConfig import *

PROJECT_NAME = os.path.basename(os.getcwd())

# toolchains options
ARCH = "arm"
CPU = "cortex-m7"
CROSS_TOOL = "gcc"

# bsp lib config
BSP_LIBRARY_TYPE = None

if os.getenv("RTT_CC"):
    CROSS_TOOL = os.getenv("RTT_CC")
if os.getenv("RTT_ROOT"):
    RTT_ROOT = os.getenv("RTT_ROOT")
# cross_tool provides the cross compiler
# EXEC_PATH is the compiler execute path, for example, CodeSourcery, Keil MDK, IAR
if CROSS_TOOL == "gcc":
    PLATFORM = "gcc"
    # this is what to define path.
    EXEC_PATH = os.getenv("EXEC_PATH")

if os.getenv("RTT_EXEC_PATH"):
    EXEC_PATH = os.getenv("RTT_EXEC_PATH")

BUILD = "debug"

if PLATFORM == "gcc":
    # toolchains
    PREFIX = "arm-none-eabi-"
    CC = PREFIX + "gcc"
    AS = PREFIX + "gcc"
    AR = PREFIX + "ar"
    CXX = PREFIX + "g++"
    LINK = PREFIX + "gcc"
    TARGET_EXT = "elf"
    SIZE = PREFIX + "size"
    OBJDUMP = PREFIX + "objdump"
    OBJCPY = PREFIX + "objcopy"

    DEVICE = " -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections"
    CFLAGS = DEVICE + " -Dgcc"
    AFLAGS = " -c" + DEVICE + " -x assembler-with-cpp -Wa,-mimplicit-it=thumb "
    LFLAGS = (
        DEVICE
        + " -Wl,--gc-sections,-Map=build/rtthread.map,-cref,-u,Reset_Handler -T debug/linker_scripts/link.lds"
    )

    CPATH = ""
    LPATH = ""

    if BUILD == "debug":
        CFLAGS += " -O0 -gdwarf-2 -g"
        AFLAGS += " -gdwarf-2"
    else:
        CFLAGS += " -O2"

    CXXFLAGS = CFLAGS
    # CFLAGS += " -std=c99"
    # CXXFLAGS += " -std=c++11"

    POST_ACTION = """mkdir -p output\nmv {}.elf output\n{} -O binary output/{}.elf output/{}.bin\n{} -O ihex output/{}.elf output/{}.hex\n{} output/{}.elf \n""".format(
        PROJECT_NAME,
        OBJCPY,
        PROJECT_NAME,
        PROJECT_NAME,
        OBJCPY,
        PROJECT_NAME,
        PROJECT_NAME,
        SIZE,
        PROJECT_NAME,
    )


def dist_handle(BSP_ROOT, dist_dir):
    import sys

    cwd_path = os.getcwd()
    sys.path.append(os.path.join(os.path.dirname(BSP_ROOT), "tools"))
    from sdk_dist import dist_do_building

    dist_do_building(BSP_ROOT, dist_dir)
