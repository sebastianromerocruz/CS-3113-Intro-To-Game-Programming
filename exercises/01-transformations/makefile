# ------------------------------------------------------------
#   Simple Makefile for a single‑source raylib program on macOS
# ------------------------------------------------------------

# ---------- 1️⃣ Sources & target ----------
SRCS   = main.cpp                # your source file(s)
TARGET = raylib_app              # name of the executable

# ---------- 2️⃣ Detect OS ----------
UNAME_S := $(shell uname -s)

# ---------- 3️⃣ Compiler & basic flags ----------
CXX      = g++                   # or clang++ if you prefer
CXXFLAGS = -std=c++11 -Wall -Wextra

# ---------- 4️⃣ macOS‑specific configuration ----------
ifeq ($(UNAME_S),Darwin)

    # Detect Apple‑silicon vs Intel Homebrew prefix
    ifeq ($(shell uname -m),arm64)
        BREW_PREFIX = /opt/homebrew
    else
        BREW_PREFIX = /usr/local
    endif

    # Tell the compiler where the header lives
    CXXFLAGS += -I$(BREW_PREFIX)/include

    # Tell the linker where the library lives
    LDFLAGS  += -L$(BREW_PREFIX)/lib

    # Optional: force a native arm64 binary (g++ will do this anyway)
    CXXFLAGS += -arch arm64

    # Link against raylib + the macOS frameworks it needs
    LIBS = -lraylib \
           -framework OpenGL \
           -framework Cocoa \
           -framework IOKit \
           -framework CoreVideo

    RUN_CMD = ./$(TARGET)

# ---------- 5️⃣ Windows (MinGW) ----------
else ifneq (,$(findstring MINGW,$(UNAME_S)))
    CXXFLAGS += -IC:/raylib/include
    LDFLAGS  += -LC:/raylib/lib
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET := $(TARGET).exe
    RUN_CMD = $(TARGET)

# ---------- 6️⃣ Linux (fallback) ----------
else
    LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    RUN_CMD = ./$(TARGET)
endif

# ---------- 7️⃣ Build rule ----------
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# ---------- 8️⃣ Convenience targets ----------
.PHONY: clean run

clean:
	rm -f $(TARGET) $(TARGET).exe

run: $(TARGET)
	$(RUN_CMD)