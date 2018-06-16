# Folders
SRCDIR = src
OBJDIR = obj
SUBFOLDERS = test test/test2
OBJSUBFOLDERS = $(OBJDIR) $(addprefix $(OBJDIR)/, $(SUBFOLDERS))
SRCSUBFOLDERS = $(SRCDIR) $(addprefix $(SRCDIR)/, $(SUBFOLDERS))

# Just for me so I can read my own makefile :o
CURRENT_TARGET = $@
CURRENT_DEPENDENCY = $<

# Get sources from /src and /src/test/ and /src/test/test2/
SOURCES = $(foreach dir, $(SRCSUBFOLDERS), $(wildcard $(dir)/*.cpp $(dir)/*.cxx))
# Source file without the /src at the start, then take the basename, then add .o, then add obj/ to the front
OBJECTS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(patsubst src/%, %, $(SOURCES)))))

# Compiling
CC = g++
INC_PATHS = -I./src
CFLAGS = -Wall -Werror -g -std=c++11 $(INC_PATHS)
LFLAGS = -lstdc++ $(CFLAGS)
TARGET_FILE = state_machine_test

# Main target 'make debug'
.phony: debug
debug: print_vars create_dirs $(OBJECTS)
	@echo building: gcc $(OBJECTS) -o $(TARGET_FILE)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(OBJDIR)/$(TARGET_FILE)

# Compiling each file
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $(CURRENT_DEPENDENCY) -o $(CURRENT_TARGET)

.phony: run
run: debug
	cd $(OBJDIR); ./$(TARGET_FILE) > ./$(TARGET_FILE).log
	geany $(OBJDIR)/$(TARGET_FILE).log &

.phony: profileing
profileing: CFLAGS += -pg
profileing: debug
	cd $(OBJDIR); ./$(TARGET_FILE) > ./$(TARGET_FILE).log
	cd $(OBJDIR); gprof $(TARGET_FILE) > ./$(TARGET_FILE).prof
	geany $(OBJDIR)/$(TARGET_FILE).log $(OBJDIR)/$(TARGET_FILE).prof &

.phony: memcheck
memcheck: debug
	cd $(OBJDIR); valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./$(TARGET_FILE) 2> ./$(TARGET_FILE).mem 1> ./$(TARGET_FILE).log
	tail $(OBJDIR)/$(TARGET_FILE).mem -n 1
	geany $(OBJDIR)/$(TARGET_FILE).log $(OBJDIR)/$(TARGET_FILE).mem &

.phony: create_dirs
create_dirs:
	mkdir -p obj

.phony: print_vars
print_vars:
	@echo VARIABLES
	@echo '   Directory: $(shell pwd)'
	@echo '   SOURCES:   $(SOURCES)'
	@echo '   OBJECTS:   $(OBJECTS)'

/phony: clean
clean:
	rm -r $(OBJDIR)
