#
# sensor lib Makefile
#
ifeq ($(MAPI_PARAM_FILE), ) 
    MAPI_PARAM_FILE:=../../../../../../Makefile.param
    OSTYPE=HuaweiLite
    include $(MAPI_PARAM_FILE)
endif

ARFLAGS = rcv
ARFLAGS_SO = $(LIBS_LD_CFLAGS)
ARFLAGS_SO += -shared -fPIC -o
CFLAGS  += -Wall -fPIC
CFLAGS  += -O2
CFLAGS  += $(LIBS_CFLAGS)
CFLAGS  += -I$(REL_INC)
CFLAGS  += -I$(NDK_PATH)/code/mediaserver/configs/dis/include

COMPILE = $(CC) $(CFLAGS) $(DFLAGS) -lm

OBJPATH = ./obj

$(OBJPATH)/%.o: ./%.c
#	@[ -e $(LIBPATH) ] || mkdir $(LIBPATH)
	@[ -e $(OBJPATH) ] || mkdir $(OBJPATH)
	@$(COMPILE) -o $@ -c $<

SRCS = $(wildcard ./*.c)
OBJS = $(SRCS:%.c=%.o)
OBJS := $(OBJS:./%=obj/%)

TARGETLIB := ./libdis_cfg_ov9732.a
TARGETLIB_SO := ./libdis_cfg_ov9732.so

all:$(TARGETLIB)
$(TARGETLIB):$(OBJS)
	@($(AR) $(ARFLAGS) $(TARGETLIB) $(OBJS))
	@($(CC) $(ARFLAGS_SO) $(TARGETLIB_SO) $(OBJS))

clean:
	@$(RM) -rf $(TARGETLIB) $(OBJS) $(TARGETLIB_SO)
	@$(RM) -rf $(LIBPATH) $(OBJPATH)
