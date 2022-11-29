CXX       = g++
CXX_FILES = ./src/main.cpp ./src/parsing.cpp ./src/utility.cpp ./src/instructions.cpp
TARGET    = ./bin/railway-asm-x16
CXXFLAGS  = -g -std=c++17 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILES) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe
