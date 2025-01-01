# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Libraries for Linux and Windows (will use pkg-config for both)
LINUX_LIBS = $(shell pkg-config --libs freeglut opengl)
WIN_LIBS = -lmingw32 -lGL -lGLU -lglut -lopengl32 -lglu32

# Include paths for Linux and Windows (pkg-config for Linux)
LINUX_INCLUDE = $(shell pkg-config --cflags freeglut opengl)

# Source files
SRCS = $(wildcard src/*.cpp)

# Object files
LINUX_OBJS = $(SRCS:.cpp=.linux.o)
WIN_OBJS = $(SRCS:.cpp=.win.o)

# Executable names
LINUX_TARGET = solar-system-linux
WIN_TARGET = solar-system.exe

# Default target
all: $(LINUX_TARGET) $(WIN_TARGET)

# Link the Linux executable
$(LINUX_TARGET): $(LINUX_OBJS)
	$(CXX) -o $@ $^ $(LINUX_LIBS)

# Link the Windows executable
$(WIN_TARGET): $(WIN_OBJS)
	x86_64-w64-mingw32-g++ -o $@ $^ $(WIN_LIBS)

# Compile source files to object files for Linux
%.linux.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LINUX_INCLUDE) -c $< -o $@

# Compile source files to object files for Windows
%.win.o: %.cpp
	x86_64-w64-mingw32-g++ $(CXXFLAGS) -I/usr/x86_64-w64-mingw32/include/GL -c $< -o $@

# Clean up build files
clean:
	rm -f $(LINUX_OBJS) $(WIN_OBJS) $(LINUX_TARGET) $(WIN_TARGET)

# Run the Linux program
run-linux: $(LINUX_TARGET)
	./$(LINUX_TARGET)

# Run the Windows program (if compiled for Windows)
run-windows: $(WIN_TARGET)
	./$(WIN_TARGET)

.PHONY: all clean run-linux run-windows
