# Makefile for C++ coding repository
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -pthread
SRCDIR = .
BUILDDIR = build

# Default target
.PHONY: all clean help

help:
	@echo "Available targets:"
	@echo "  compile FILE=<path>  - Compile a specific C++ file to build/ directory"
	@echo "  run FILE=<path>      - Compile and run a specific C++ file"
	@echo "  r FILE=<path>        - Short alias for run"
	@echo "  clean               - Remove all executables from build/"
	@echo "  help                - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make run FILE=multithreading/basic.cpp"
	@echo "  make r FILE=multithreading/basic.cpp"
	@echo "  ./run multithreading/basic.cpp"
	@echo ""
	@echo "All executables are created in the build/ directory"

# Create directories
$(BUILDDIR):
	mkdir -p $@

# Compile a specific file
compile: $(BUILDDIR)
ifndef FILE
	@echo "Error: Please specify FILE=<path>"
	@echo "Example: make compile FILE=multithreading/basic.cpp"
	@exit 1
endif
	@echo "Compiling $(FILE)..."
	$(CXX) $(CXXFLAGS) $(FILE) -o $(BUILDDIR)/$(basename $(notdir $(FILE)))

# Compile and run
run: compile
	@echo "Running $(basename $(notdir $(FILE)))..."
	@echo "----------------------------------------"
	@./$(BUILDDIR)/$(basename $(notdir $(FILE)))
	@echo "----------------------------------------"

# Short alias for run
r: run

# Clean executables
clean:
	rm -rf $(BUILDDIR)/*
	@echo "Cleaned build artifacts"

.PHONY: compile run r clean help