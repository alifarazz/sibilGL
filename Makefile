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
# Packages
PACKAGES=glfw3 glew glm

TARGET = main

CCFLAGS = $(WARN) $(PTHREAD) -std="$(STD)"  -stdlib=libstdc++  $(OPT) -pipe `pkg-config --cflags $(PACKAGES)`
LDFLAGS = $(PTHREAD) `pkg-config --libs $(PACKAGES)` # -export-dynamic

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
