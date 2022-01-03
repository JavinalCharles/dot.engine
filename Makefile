TARGET = ./lib/libsigma.a
CC = g++

INC_DIR = ./include
BUILD_DIR = ./build
SRC_DIR = ./src

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

INC_FLAGS = $(addprefix -I,$(INC_DIR))
CPPFLAGS = $(INC_FLAGS) -std=c++17
LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LIBFLAGS)

$(TARGET): $(OBJS)
	ar rcs $@ $(OBJS)
.PHONY: all
all: $(TARGET)

.PHONY: static
static: $(STATIC)

.PHONY: clean
clean:
	rm $(BUILD_DIR)/* ./lib/*