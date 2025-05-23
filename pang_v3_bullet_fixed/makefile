# ---- Configuración de compilador y flags ----
CXX       := g++
CXXFLAGS  := -std=c++11 -Wall -I. -MMD -MP
LDFLAGS   := -Wl,--copy-dt-needed-entries
LDLIBS    := -lGL -lGLU -lglut -lm -lX11

# ---- Fuentes y objetos ----
SRCS      := Animalito.cpp Shape.cpp Ball.cpp Bullet.cpp \
             Man.cpp GLstuff.cpp ObjectsList.cpp mainPANG.cpp
OBJS      := $(SRCS:.cpp=.o)
DEPS      := $(SRCS:.cpp=.d)

# ---- Ejecutable final ----
TARGET    := PANG

# ---- Reglas ----
.PHONY: all clean

all: $(TARGET)

# ---- Linkeo ----
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# ---- Compilación genérica con generación de dependencias ----
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Incluye automáticamente los makefiles de dependencias (.d)
-include $(DEPS)

# ---- Elimina todo lo generado ----
clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
