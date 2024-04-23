# Compiler, compiler and Linker flags.
CC := gcc
CFLAGS := -Ilib/SDL/include -Wall -MMD
LDFLAGS := -Llib/SDL/lib -Lbin/obj 
LDLIBS := -lm -lSDL2main -lSDL2

# Platform conditional compilation
ifeq ($(OS),Windows_NT)
	CFLAGS += -mwindows
	LDLIBS := -lmingw32 $(LDLIBS)
endif

# Source dir, object and dependency file gen dir.
SRCDIR := ./src
OBJDIR := ./bin/obj

# Source, object and dependency file names. 
SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.d, $(SRCS))
EXEC := ./bin/renderer.exe

.PHONY: init run clean

# Build if needed and run the executable produced.
run: $(EXEC)
	$(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(EXEC)

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

