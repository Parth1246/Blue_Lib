# Source files and Includes path for makefile

SOURCES = $(wildcard ./src/*.c )
  
INCLUDES = -I ./include/CMSIS \
           -I ./include/common \
           -I ./include/stm32 \
           -I ./include/qfp

LIBS = libqfp.a