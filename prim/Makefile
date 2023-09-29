CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC_DIR = src
OBJ_DIR = obj

_SRC = heap.c graph.c
_OBJ = $(_SRC:.c=.o)
SRC = $(patsubst %, $(SRC_DIR)/%, $(_SRC))
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))


all: prim

lib: $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

prim: lib
	$(CC) $(CFLAGS) prim.c $(OBJ) -o prim

clean:
	rm -f $(OBJ_DIR)/*.o prim