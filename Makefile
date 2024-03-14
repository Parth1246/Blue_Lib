#-----------------------------------------------------------------------------
# Simple make file to support build and flash of executables
#
# Use: make [TARGET] [EXECUTABLE_NAME]
#
# Build Targets:
#      <FILE>.o - Builds a <FILE>.o object file
#      all - Builds binary and elf files in project (links as well)
#      clean - Removes all generated files
#      flash - Flash binary file into target platform
#      erase - Performs Full chip erase
#
# executable name:
#     Ex.  make all TARGET=test_gpio
#
# Author: kaushal dekivadia
# Date:   March 12, 2022
#------------------------------------------------------------------------------

include source.mk

TARGET := 
OS = Windows
 
ifeq ($(OS),Windows)
    DELETE = del /f
else
    DELETE = rm -
endif

BINPATH = $(shell  cd)\$(TARGET).bin


TEST_PATH = test/

LIB_PATH = lib/
# Architecture Specifications and flags

MARCH = armv7-m
CPU = cortex-m3

LINKERFILE = stm32f103xx.lds


#compilers flags and defines

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld.bfd
SIZE = arm-none-eabi-size
OBJCOPY = arm-none-eabi-objcopy


CFLAGS = -mcpu=$(CPU) -march=$(MARCH) -mthumb -std=c99 -Wall -O0 -g -MMD -fdata-sections -ffunction-sections


LDFLAGS = -Map=$(TARGET).map -T $(LINKERFILE) -o0  --gc-sections $(LIB_PATH)libqfp.a
CPPFLAGS = -DSTM32F10X_MD $(INCLUDES) 

LOADER = ST-LINK_CLI

#The --ffunction-sections option has ensured that each function is compiled in a separate section, which allows the linker (via -Wl,--gc-sections) to later remove any functions that are not called from the final executable.

#object files

OBJS = $(SOURCES:.c=.o)    $(TEST_PATH)$(TARGET).o 
ASMS = $(SOURCES:.c=.asm)  $(TEST_PATH)$(TARGET).asm
PREPS = $(SOURCES:.c=.i)   $(TEST_PATH)$(TARGET).i


#rules of building process

%.o:%.c
	$(CC) -c $^ $(CFLAGS) $(CPPFLAGS) -o $@

%.asm:%.c
	$(CC) -S $^ $(CFLAGS) $(CPPFLAGS) -o $@

%.i:%.c
	$(CC) -E $^ $(CPPFLAGS) -o $@

$(TEST_PATH)$(TARGET).elf:$(OBJS) $(LIB_PATH)$(LIBS)
	$(LD) $^ $(LDFLAGS) -o $@

$(TARGET).bin:$(TEST_PATH)$(TARGET).elf
	$(OBJCOPY) -O binary $^ $@

#build commands for makefile

all: $(TEST_PATH)$(TARGET).elf $(TARGET).bin

.PHONY: clean
clean:
	$(DELETE) src\*.o   src\*.d  $(TARGET).bin test\$(TARGET).elf $(TARGET).map test\*.o test\*.d src\*.asm src\*.i

.PHONY: erase
erase:
	$(LOADER)  erase

.PHONY: flash
flash:
	$(LOADER) -P $(BINPATH) 0x08000000 -V "after_programming" -Cksum $(BINPATH)
