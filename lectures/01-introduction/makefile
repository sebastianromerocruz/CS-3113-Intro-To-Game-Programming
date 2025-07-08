# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -arch arm64

# Source Files
SRCS = main.cpp

# Output Executable
TARGET = raylib_app

# Raylib and Frameworks (macOS-specific)
LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Build rule
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# Clean rule
clean:
	rm -f $(TARGET)

# Run rule (builds the target and then executes it)
run: $(TARGET)
	./$(TARGET)
