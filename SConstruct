import os
import sys
import rtconfig
from config.log import Log
from config.allConfig import *

log = Log("Sconstruct")
LOCAL_ROOT = os.getcwd()

TARGET = "{}.elf".format(os.path.basename(os.getcwd()))
log.info("Create the target name: {}".format(os.path.basename(os.getcwd())))

if os.getenv("RTT_ROOT"):
    RTT_ROOT = os.getenv("RTT_ROOT")
    log.info("Found RTT_ROOT path: " + RTT_ROOT)

if os.path.exists(os.path.join(LOCAL_ROOT, "libraries")):
    SDK_LIB = os.path.join(LOCAL_ROOT, "libraries")
    log.info("Found SDK library: " + SDK_LIB)
else:
    log.err("Not found SDK library!")
    sys.exit(-1)

if os.path.isdir(os.path.join(RTT_ROOT, "tools")):
    sys.path = sys.path + [os.path.join(RTT_ROOT, "tools")]
    log.info("Found tools path: " + os.path.join(RTT_ROOT, "tools"))
else:
    log.warn("Not find tools path: " + os.path.join(RTT_ROOT, "tools"))
try:
    from building import *
except Exception as e:
    log.err("Error message:".format(e.message))
    log.err(
        "Cannot found RT-Thread root directory, please check RTT_ROOT: {}".format(
            RTT_ROOT
        )
    )
    sys.exit(-1)

Export("rtconfig")
Export("RTT_ROOT")
Export("SDK_LIB")


DefaultEnvironment(tools=[])

env = Environment(
    tools=["mingw"],
    AS=rtconfig.AS,
    ASFLAGS=rtconfig.AFLAGS,
    CC=rtconfig.CC,
    CCFLAGS=rtconfig.CFLAGS,
    AR=rtconfig.AR,
    ARFLAGS="-rc",
    CXX=rtconfig.CXX,
    CXXFLAGS=rtconfig.CXXFLAGS,
    LINK=rtconfig.LINK,
    LINKFLAGS=rtconfig.LFLAGS,
)
env.PrependENVPath("PATH", rtconfig.EXEC_PATH)

env.AppendUnique(CPPDEFINES=[])


# prepare building environment
objs = PrepareBuilding(env, RTT_ROOT, has_libcpu=False)

rtconfig.BSP_LIBRARY_TYPE = STM32_LIBRARY

if not SDK_LIB:
    objs.extend(SConscript(os.path.join(SDK_LIB, "SConscript")))

# objs += PrepareBuilding(env, LIB_ROOT, has_libcpu=False)
# make a building
DoBuilding(TARGET, objs)
