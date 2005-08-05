## Copyright 2003 MakingThings LLC.

####### Compiler, tools and options

#
# call with "make <TARGET=target>"
#
# valid target is one of:
#        linux
#        zaurus 
#        macosx
#        unc20
#

ifndef ($(TARGET))
	TARGET = linux
endif

ifeq ($(TARGET),zaurus)
CC      =       /opt/Embedix/tools/bin/arm-linux-gcc
AR      =       /opt/Embedix/tools/bin/arm-linux-ar
PTHREAD	=	-pthread
TELEOLIB        =       teleolib_linux_arm.a
CFLAGS  =	-Wall
endif

ifeq ($(TARGET),linux)
CC      =       gcc
AR      =       ar
PTHREAD	=	-pthread
CFLAGS  =	-Wall
TELEOLIB        =       teleolib_linux_x86.a
endif

ifeq ($(TARGET),macosx)
CC      =       gcc
AR      =       ar
PTHREAD	=	-lpthread
TELEOLIB        =       teleolib_macos_x.a
CFLAGS  =	-Wall -DMACOSX
endif

ifeq ($(TARGET),unc20)
LXNETES_TOOLCHAIN_PATH = /usr/local/LxNETES-2.2/arm-elf/
CC=$(LXNETES_TOOLCHAIN_PATH)/uClibc-0.9.19/bin/arm-uclibc-gcc
CFLAGS = -I$(INCDIR) -Os -fomit-frame-pointer \
         -elf2flt -static -Wall  -DEMBED \
        -Dlinux -D__linux__ \
        $(EXTRA_CFLAGS)
LDFLAGS :=  -Wall -elf2flt -static
LINK := $(CC) $(EXTRA_LDFLAGS_PREFIX) $(LDFLAGS)
PTHREAD	=	-lpthread
VPATH = /usr/local/LxNETES-2.2/arm-elf/uClibc-0.9.19/lib
TELEOSYS	=	Linux
TELEOLIB	=	teleolib_linux_unc20.a
endif


all: intro_button_output intro_light intro_pwm intro_chart intro_button tct tmt tdt button light chart stepper motor 

clean: 
	/bin/rm -f *.o intro_button_output intro_pwm intro_light intro_chart intro_button tct tmt tdt button light chart stepper  motor stepAndLight

LIBINC = ../include/

INC = -I$(LIBINC)

COMMONINCS = $(LIBINC)TeleoModuleManager.h \
       $(LIBINC)TeleoChannel.h       \
       $(LIBINC)TeleoUtil.h          \
       $(LIBINC)TeleoInterface.h 


tct: $(COMMONINCS) TeleoChannelTest.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o tct TeleoChannelTest.c ../lib/$(TELEOLIB) $(INC)

tmt: $(COMMONINCS) TeleoModuleTest.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o tmt TeleoModuleTest.c ../lib/$(TELEOLIB) $(INC)

tdt: $(COMMONINCS) TeleoDeviceTest.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o tdt TeleoDeviceTest.c ../lib/$(TELEOLIB) $(INC)

button: $(COMMONINCS) button.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o button button.c ../lib/$(TELEOLIB) $(INC)

intro_button: $(COMMONINCS) intro_button.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o intro_button intro_button.c ../lib/$(TELEOLIB) $(INC)

intro_button_output: $(COMMONINCS) intro_button_output.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o intro_button_output intro_button_output.c ../lib/$(TELEOLIB) $(INC)

intro_light: $(COMMONINCS) intro_light.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o intro_light intro_light.c ../lib/$(TELEOLIB) $(INC)

intro_pwm: $(COMMONINCS) intro_pwm.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o intro_pwm intro_pwm.c ../lib/$(TELEOLIB) $(INC)

light: $(COMMONINCS) $(COMMONSRC) light.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o light light.c ../lib/$(TELEOLIB) $(INC)

lightOn: $(COMMONINCS) $(COMMONSRC) lightOn.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o lightOn lightOn.c ../lib/$(TELEOLIB) $(INC)

chart: $(COMMONINCS) $(COMMONSRC) chart.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o chart chart.c ../lib/$(TELEOLIB) $(INC)

intro_chart: $(COMMONINCS) $(COMMONSRC) intro_chart.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o intro_chart intro_chart.c ../lib/$(TELEOLIB) $(INC)

stepper: $(COMMONINCS) $(COMMONSRC) stepper.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o stepper stepper.c ../lib/$(TELEOLIB) $(INC)

motor: $(COMMONINCS) $(COMMONSRC) motor.c ../lib/$(TELEOLIB)
	$(CC) $(PTHREAD) $(CFLAGS) -g -o motor motor.c ../lib/$(TELEOLIB) $(INC)
