CXX = g++
CXXFLAGS = -std=c++11 `pkg-config --cflags gtkmm-3.0`
LDFLAGS = `pkg-config --libs gtkmm-3.0`
INCLUDES = -Iinclude

TARGET = bin/DrawingApp

# Trouver tous les fichiers source dans le répertoire src
SRCS := $(wildcard src/*.cpp)

# Remplacer le répertoire src par lib et l'extension .cpp par .o
OBJS := $(patsubst src/%.cpp, lib/%.o, $(SRCS))

# Remplacer le répertoire src par lib et l'extension .cpp par .dpp
DEPS := $(patsubst src/%.cpp, lib/%.dpp, $(SRCS))

all: recompile run

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

lib/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

lib/%.dpp: src/%.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MM $< | sed 's|src/\(.*\)\.o|lib/\1.o lib/\1.dpp:|' > $@

compile: $(OBJS)

recompile: clean compile

# Inclure les fichiers de dépendances s'ils existent
-include $(DEPS)

init:
	@mkdir -p bin
	@mkdir -p lib

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)
	rm -rf lib/*.*

.PHONY: all clean init run
