PROJECT = sebastion

SHARED_DIR = inc
CXXSTD = -std=c++17
OOCD_INTERFACE = stlink-v2
OOCD_TARGET = stm32f4x
OPENCM3_LIB = opencm3_stm32f4
OPENCM3_DEFS = -DSTM32F4
OPT = -Og -g3

SOURCE_DIR = src
CXXFILES := $(shell find $(SOURCE_DIR) -name '*.cpp')

# TODO - you will need to edit these two lines!
DEVICE = stm32f411ce

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))

CONFIG_DIR = cfg
VPATH += $(CONFIG_DIR)
INCLUDES += $(patsubst %,-I%, . $(CONFIG_DIR))

OPENCM3_DIR = lib/libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
