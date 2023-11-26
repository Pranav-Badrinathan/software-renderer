SOURCE = ./src/main.c ./src/draw.c ./src/linalg.c ./src/input.c
COMPILER_FLAGS = -Ilib/SDL/include -Wall -mwindows
EXEC = ./bin/renderer.exe

LINKER_FLAGS = -Llib/SDL/lib -lmingw32 -lSDL2main -lSDL2

CC=gcc

run: compile $(EXEC)
	$(EXEC)

compile: $(SOURCE)
	$(CC) $(SOURCE) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC)

init:
	@$(shell mkdir bin)
	@$(shell cp lib\SDL\bin\SDL2.dll bin\)
	@echo Finished Initialization
