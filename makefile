CXX       = g++
CXX_FILES = ./src/main.cpp ./src/utility.cpp ./src/parsing.cpp ./src/assembler/instructions.cpp ./src/assembler/assembler.cpp ./src/linker/stitcher.cpp ./src/linker/validator.cpp
TARGET    = ./bin/railway-asm-x8
CXXFLAGS  = -g -std=c++17 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILES) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe
