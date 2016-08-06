CXX = g++
CXXFLAGS = -c -Wall -Wextra
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -Wall -Wextra
OBJS = OBJ/close.o OBJ/init.o OBJ/main.o OBJ/texture.o OBJ/load_media.o OBJ/timer.o OBJ/helper.o

TARGET = run

all : $(TARGET)

debug : CXXFLAGS += -g
debug : C_COMPILER_FLAGS += -g
debug : all

$(TARGET) : $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

OBJ/close.o : SRC/close.cpp SRC/isolation.h
	$(CXX) $(CXXFLAGS) $< -o $@

OBJ/init.o : SRC/init.cpp SRC/isolation.h
	$(CXX) $(CXXFLAGS) $< -o $@

OBJ/main.o : SRC/main.cpp SRC/isolation.h
	$(CXX) $(CXXFLAGS) $< -o $@

OBJ/texture.o: SRC/texture.cpp SRC/isolation.h SRC/texture.h
	$(CXX) $(CXXFLAGS) $< -o $@

OBJ/load_media.o: SRC/load_media.cpp SRC/isolation.h
	$(CXX) $(CXXFLAGS) $< -o $@

OBJ/timer.o: SRC/timer.cpp SRC/timer.h SRC/isolation.h
	$(CXX) $(CXXFLAGS) $< -o $@

OBJ/helper.o: SRC/helper.cpp SRC/isolation.h
	$(CXX) $(CXXFLAGS) $< -o $@
