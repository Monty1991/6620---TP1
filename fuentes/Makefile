ifndef ARCH_TARGET
ARCH_TARGET = x86
endif

extension = c

CFLAGS = -Wall -Werror -pedantic -pedantic-errors
CFLAGS += -O0
CFLAGS += -ggdb -DDEBUG -fno-inline
CSTD = c99
LDFLAGS =

fuentes = $(wildcard *.$(extension))

obj = $(patsubst %.$(extension),%.o,$(fuentes))

EXE = qsort

ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)

CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)

.PHONY: all build clean

.all: build

ifeq ($(ARCH_TARGET), r2k)
CFLAGS +=-march=r2k 
qsort.o: qsort.S
	$(CC) $(CFLAGS) -c qsort.S -o qsort.o
else
qsort.o: qsort.c
	$(CC) $(CFLAGS) -pipe -c qsort.c -o qsort.o
endif

build: qsort.o $(obj)
	$(LD) $(obj) -o $(EXE) $(LDFLAGS)

.clean:
	$(RM) -f $(obj) $(EXE) $(EXE).exe
