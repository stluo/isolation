OBJS = close.o init.o main.o texture.o load_media.o
CC = g++
COMPILER_FLAGS = -w
C_COMPILER_FLAGS = -c -w
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
OBJ_NAME = run

all : exe

debug : COMPILER_FLAGS += -g
debug : C_COMPILER_FLAGS += -g
debug : exe

exe : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

close.o : isolation.h close.cpp
	$(CC) $(C_COMPILER_FLAGS) $(LINKER_FLAGS) close.cpp

init.o : isolation.h init.cpp
	$(CC) $(C_COMPILER_FLAGS) $(LINKER_FLAGS) init.cpp

main.o : isolation.h main.cpp
	$(CC) $(C_COMPILER_FLAGS) $(LINKER_FLAGS) main.cpp

texture.o : isolation.h texture.h texture.cpp
	$(CC) $(C_COMPILER_FLAGS) $(LINKER_FLAGS) texture.cpp

load_media.o : isolation.h load_media.cpp
	$(CC) $(C_COMPILER_FLAGS) $(LINKER_FLAGS) load_media.cpp

.PHONY : clean
clean:
	-rm $(OBJS) $(OBJ_NAME)
