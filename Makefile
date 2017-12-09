# compiler
CC=clang++
# linker
LD=$(CC)
# optimisation
OPT=-ggdb
# warnings
WARN=-Wall -Wextra
# standards
STD=c++14
# pthread
# PTHREAD=-pthread
PTHREAD=

TARGET = sibil

CCFLAGS = $(WARN) $(PTHREAD) -std="$(STD)"  -stdlib=libstdc++  $(OPT) -pipe `pkg-config --cflags glfw3 glew glm` -I/usr/include/FreeImage
LDFLAGS = $(PTHREAD) `pkg-config --libs glfw3 glew glm` -lfreeimage # -export-dynamic

SRCS = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SRCS))

.PHONY: default all clean

default: $(TARGET)

all: default

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	$(RM) *.o
	$(RM) $(TARGET)
