# ------------------------------------------------------------
#  Detect the operating system once, early in the file
# ------------------------------------------------------------
UNAME_S := $(shell uname -s)

# ------------------------------------------------------------
#  Source files
# ------------------------------------------------------------

SRCS = main.cpp CS3113/*.cpp  # entities

# ------------------------------------------------------------
#  Target name
# ------------------------------------------------------------
TARGET = raylib_app

# ------------------------------------------------------------
#  Compiler / basic flags
# ------------------------------------------------------------
CXX      = g++
CXXFLAGS = -std=c++11

# ------------------------------------------------------------
#  Raylib configuration (pkg‑config works on macOS too)
# ------------------------------------------------------------
RAYLIB_CFLAGS = $(shell pkg-config --cflags raylib)
RAYLIB_LIBS   = $(shell pkg-config --libs   raylib)

# ------------------------------------------------------------
#  Platform‑specific settings
# ------------------------------------------------------------
# ---------- macOS ----------
ifeq ($(UNAME_S),Darwin)
    # Add the architecture flag you need (arm64 or x86_64)
    CXXFLAGS += -arch arm64 $(RAYLIB_CFLAGS)

    # Use the frameworks that ship with macOS
    LIBS = $(RAYLIB_LIBS) \
           -framework OpenGL \
           -framework Cocoa \
           -framework IOKit \
           -framework CoreVideo

    EXEC = ./$(TARGET)

# ----- Windows ----------
else ifneq (,$(findstring MINGW,$(UNAME_S)))   
    CXXFLAGS += -IC:/raylib/include
    LIBS = -LC:/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET := $(TARGET).exe
    EXEC = ./$(TARGET)

# --------- Linux ----------
else                                         
    CXXFLAGS += $(RAYLIB_CFLAGS)
    LIBS = $(RAYLIB_LIBS) -lGL -lm -lpthread -ldl -lrt -lX11
    EXEC = ./$(TARGET)
endif

# ------------------------------------------------------------
#  Build rule
# ------------------------------------------------------------
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LIBS)

# ------------------------------------------------------------
#  Convenience targets
# ------------------------------------------------------------
.PHONY: clean run

clean:
	@rm -f $(TARGET) $(TARGET).exe

run: $(TARGET)
	$(EXEC)