# Raylib Proof of Concept
A sample raylib app based on CS3113's [**user input**](https://github.com/sebastianromerocruz/CS3113-material/tree/main/lectures/player-input) lecture.

For Mac, the steps I had to take to get this to work were the following:

### Step 1: Install Homebrew (if not already installed)
If you don't have Homebrew installed, you can install it by running this command in your terminal:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### Step 2: Install CMake
Once Homebrew is installed, you can install CMake by running the following command:

```bash
brew install cmake
```

### Step 3: Verify CMake Installation
To confirm that CMake was installed correctly, run:

```bash
cmake --version
```

This should return the installed version of CMake.

### Step 4: Install Raylib
After installing CMake, you can proceed with the Raylib instructions:

1. Clone Raylib:

   ```bash
   git clone https://github.com/raysan5/raylib.git
   cd raylib
   ```

2. Build Raylib for `arm64` using CMake:

   ```bash
   mkdir build
   cd build
   cmake -DCMAKE_OSX_ARCHITECTURES=arm64 ..
   make
   sudo make install
   ```

### Step 5: `makefile` Contents

You can create a `Makefile` to automate running our g++ command. Below is an example of how you can structure a `Makefile` to compile and run your Raylib application automatically:

```makefile
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
```

### How to use the Makefile:

1. **Compile the program:**

   ```bash
   make
   ```

   This will build the program (if it's not already built).

2. **Run the program:**

   You can now use:

   ```bash
   make run
   ```

   This will first compile the program (if needed) and then execute it (`./raylib_app`).

3. **Clean the project:**

   You can still use:

   ```bash
   make clean
   ```

   This will remove the compiled executable.

This setup lets you build and run the Raylib application with a single `make run` command.

### Sample Behaviour

![test](assets/test.gif)

<sub>**Figure 1**: Expected behaviour. Use arrow keys to move the shield around and the `esc` to close the window.</sub>