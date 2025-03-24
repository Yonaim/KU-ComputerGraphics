CXX := g++
CXXFLAGS := -std=c++17 -O2 -Iinclude -g3
# CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Iinclude -g3
# CXXFLAGS := -std=c++17 -O2 -Iinclude -DGL_SILENCE_DEPRECATION
CPPFLAGS = -I./include
LDFLAGS := -L/opt/homebrew/lib -lglfw -L./lib -lglad -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

SRCDIR := src
OBJDIR := obj

SOURCES := $(wildcard $(SRCDIR)/*.cpp) 
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))
EXEC := ray-tracer.out

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJECTS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

re:
	make clean
	make all
