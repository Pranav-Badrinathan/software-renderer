SOURCE = ./src/main.c
INCLUDE = -Ilib/SDL/include
EXEC = ./bin/renderer.exe

LINKER_FLAGS = -Llib/SDL/lib -lmingw32 -lSDL2main -lSDL2

run: compile $(EXEC)
	$(EXEC)

compile: $(SOURCE)
	gcc $(SOURCE) $(INCLUDE) $(LINKER_FLAGS) -o $(EXEC)
