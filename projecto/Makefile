CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2
INCLUDES = -Iinclude
TARGET = biblioteca
SRCDIR = src
OBJDIR = obj
INCDIR = include
DATADIR = data

SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
HEADERS = $(wildcard $(INCDIR)/*.h)
DEPENDS = $(OBJECTS:.o=.d)

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
NC = \033[0m 

all: $(TARGET)
	@echo "$(GREEN) Compilación completada exitosamente$(NC)"
	@echo "$(BLUE)Ejecute './$(TARGET)' para iniciar el programa$(NC)"

$(TARGET): $(OBJECTS) | $(DATADIR)
	$(CXX) $(OBJECTS) -o $@
	@echo "$(GREEN)✓ Ejecutable '$(TARGET)' creado$(NC)"

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	@echo "$(YELLOW)Compilando $<...$(NC)"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

$(OBJDIR):
	@echo "$(BLUE)Creando directorio de objetos...$(NC)"
	mkdir -p $(OBJDIR)/$(SRCDIR)

$(DATADIR):
	@echo "$(BLUE)Creando directorio de datos...$(NC)"
	mkdir -p $(DATADIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "$(GREEN)✓ Limpieza completada$(NC)"

# Include dependency files
-include $(DEPENDS)

distclean: clean
	@echo "$(RED)Limpieza completa...$(NC)"
	rm -rf $(DATADIR)/*.txt
	@echo "$(GREEN)✓ Limpieza completa terminada$(NC)"

run: $(TARGET)
	@echo "$(BLUE)Ejecutando $(TARGET)...$(NC)"
	./$(TARGET)

install-deps:
	@echo "$(YELLOW)Verificando dependencias...$(NC)"
	@which $(CXX) > /dev/null || (echo "$(RED)Error: $(CXX) no encontrado$(NC)" && exit 1)
	@echo "$(GREEN)✓ Todas las dependencias están instaladas$(NC)"

setup-data: | $(DATADIR)
	@echo "LIBRO|El Quijote|Miguel de Cervantes|9788424193096|1605|3|3|Novela|1072" > $(DATADIR)/materiales.txt
	@echo "LIBRO|Cien años de soledad|Gabriel García Márquez|9788497592208|1967|2|2|Realismo mágico|471" >> $(DATADIR)/materiales.txt
	@echo "LIBRO|1984|George Orwell|9788499890944|1949|5|4|Distopía|326" >> $(DATADIR)/materiales.txt
	@echo "Juan Pérez|12345678|juan.perez@email.com|5|" > $(DATADIR)/usuarios.txt
	@echo "María García|87654321|maria.garcia@email.com|3|" >> $(DATADIR)/usuarios.txt
	@echo "Carlos López|11223344|carlos.lopez@email.com|5|9788499890944" >> $(DATADIR)/usuarios.txt
	@echo "11223344|9788499890944|$(shell date +%s)|0|1" > $(DATADIR)/prestamos.txt
	@echo "$(GREEN)✓ Archivos de datos de ejemplo creados$(NC)"

memcheck: $(TARGET)
	@echo "$(YELLOW)Verificando memoria con valgrind...$(NC)"
	@which valgrind > /dev/null || (echo "$(RED)valgrind no encontrado$(NC)" && exit 1)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

info:
	@echo "$(BLUE)================================================$(NC)"
	@echo "$(BLUE)  Sistema de Gestión de Biblioteca Digital$(NC)"
	@echo "$(BLUE)================================================$(NC)"
	@echo "Compilador: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "Archivos fuente: $(words $(SOURCES))"
	@echo "Directorio de objetos: $(OBJDIR)"
	@echo "Directorio de datos: $(DATADIR)"
	@echo "Ejecutable: $(TARGET)"
	@echo "$(BLUE)================================================$(NC)"

help:
	@echo "$(BLUE)Comandos disponibles:$(NC)"
	@echo "  $(GREEN)make$(NC) o $(GREEN)make all$(NC)     - Compilar el proyecto"
	@echo "  $(GREEN)make run$(NC)            - Compilar y ejecutar"
	@echo "  $(GREEN)make distclean$(NC)      - Limpieza completa"
	@echo "  $(GREEN)make install-deps$(NC)   - Verificar dependencias"
	@echo "  $(GREEN)make memcheck$(NC)       - Verificar memoria (requiere valgrind)"
	@echo "  $(GREEN)make info$(NC)           - Mostrar información del proyecto"
	@echo "  $(GREEN)make help$(NC)           - Mostrar esta ayuda"

package: clean
	@echo "$(YELLOW)Creando paquete para entrega...$(NC)"
	tar -czf biblioteca-sistema.tar.gz src/ include/ main.cpp Makefile README.md instrucciones.md
	@echo "$(GREEN)✓ Paquete 'biblioteca-sistema.tar.gz' creado$(NC)"

check-style:
	@echo "$(YELLOW)Verificando estilo de código...$(NC)"
	@which cppcheck > /dev/null || (echo "$(RED)cppcheck no encontrado$(NC)" && exit 1)
	cppcheck --enable=all --std=c++17 $(SRCDIR)/ main.cpp

.PHONY: all clean distclean run install-deps setup-data memcheck info help package check-style
.DEFAULT_GOAL := all

.PRECIOUS: $(OBJDIR)/%.o

ifndef VERBOSE
.SILENT:
endif
