CC = gcc
CFLAGS = -I ./include
C_SRC = $(wildcard *.c)
C_EXE = $(patsubst %.c, %, $(C_SRC))
CPP_SRC = $(wildcard *.cpp)
CPP_EXE = $(patsubst %.cpp, %, $(CPP_SRC))

.PHONY:all clean

all:$(CPP_EXE) $(C_EXE)

.c:
	$(CC) $(CFLAGS) -o $@ $<

.cpp:
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.exe *.o