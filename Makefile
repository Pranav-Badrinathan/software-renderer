# Compiler, compiler and Linker flags.
CC=gcc
CFLAGS = -Ilib/SDL/include -Wall -mwindows -MMD
LDFLAGS = -Llib/SDL/lib -Lbin/obj -lmingw32 -lSDL2main -lSDL2

# Source dir, object and dependency file gen dir.
SRCDIR = ./src
OBJDIR = ./bin/obj

# Source, object and dependency file names. 
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.d, $(SRCS))
EXEC = ./bin/renderer.exe

.PHONY: init run clean

# Build if needed and run the executable produced.
run: $(EXEC)
	$(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(EXEC)

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(OBJDIR):
	@mkdir -p ./bin/obj

init:
	@mkdir -p bin
	@cp ./lib/SDL/bin/SDL2.dll ./bin/
	@echo Finished Initialization

clean:
	rm -f ./bin/obj/*.o ./bin/obj/*.d

