CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC_DIR = src
OBJ_DIR = obj

_SRC = bf_graph.c
_OBJ = $(_SRC:.c=.o)
SRC = $(patsubst %, $(SRC_DIR)/%, $(_SRC))
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))


all: bellman_ford

lib: $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
\
bellman_ford: lib
	$(CC) $(CFLAGS) bellman_ford.c $(OBJ) -o bellman_ford

comp_to_root: lib
	$(CC) $(CFLAGS) bellman_ford.c $(OBJ) -o ../bf && make clean

clean:
	rm -f $(OBJ_DIR)/*.o bellman_ford