
MODULE_NAME = video_sensor_libs

$(MODULE_NAME)_PLATFORM_DEPENDENCY = yes
$(MODULE_NAME)_CORE_DEPENDENCY = yes

INCDIR = . include
INCDIR += $($(MAKEAPPNAME)_PATH)/src/include

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = bios xdc pdk vision_sdk xdais \
	starterware_hal fat_lib utils_platform \
	links_fw links_fw_rtos

MODULE_SRC_BASE_PATH := $($(MAKEAPPNAME)_PATH)/src/rtos/video_sensor

CFLAGS_LOCAL_$(CORE) = $(vision_sdk_CFLAGS)

# Common source files and CFLAGS across all platforms and cores
CFLAGS_LOCAL_COMMON = $(vision_sdk_CFLAGS)

include $(MODULE_SRC_BASE_PATH)/src/SRC_FILES.MK

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
include $(ROOTDIR)/build/rtos/makerules/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
