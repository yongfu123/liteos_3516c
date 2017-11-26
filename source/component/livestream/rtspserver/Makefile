HIARCH := hi3518e
OSTYPE := HuaweiLite
CROSS_COMPILE = arm-hisiv500-linux-

LITEOSTOPDIR := $(shell pwd)/../../../../osdrv/$(HIARCH)/$(OSTYPE)/opensource/liteos/liteos

include $(LITEOSTOPDIR)/config.mk


ARFLAGS = cr
OUT = ./lib/
LIB = $(OUT)/librtsp.a

CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
AR = $(CROSS_COMPILE)ar

LITEOS_CFLAGS += -I $(LITEOSTOPDIR)/net/lwip_sack/include/lwip
LITEOS_CFLAGS += -I $(shell pwd)/include

RM = -rm -rf

SRCS = $(wildcard src/*.c)
COBJS = $(patsubst %.c, %.o,$(SRCS))

all: $(LIB)
	
$(COBJS): %.o : %.c
	@$(CC) $(LITEOS_CFLAGS) -c $< -o $@

OBJS = $(COBJS)

$(LIB): $(OBJS)
	@mkdir -p $(OUT)
	@$(AR) $(ARFLAGS) $@ $(OBJS)

clean:
	@$(RM) $(OBJS) $(LIB) $(OUT) *.bak *~

.PHONY: all clean
