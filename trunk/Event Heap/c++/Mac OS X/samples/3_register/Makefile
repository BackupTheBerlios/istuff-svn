CC = gcc-3.3

PLATFORM_DIR = ../..

CFLAGS = -g -Dunix -D_REENTRANT -I$(PLATFORM_DIR)/include 
LIBS = -L$(PLATFORM_DIR)/lib ../../lib/libceheap2.a ../../lib/libidk.a -lstdc++

# Change this to the name of your program
PROG = register

# Change this to the name of your source file
OBJS = register.cpp

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG) $(LIBS)
	
clean:
	rm $(PROG)