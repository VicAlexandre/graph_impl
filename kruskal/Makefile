CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC_DIR = src
OBJ_DIR = obj

_SRC = graph.c union_find.c quicksort.c
_OBJ = $(_SRC:.c=.o)
SRC = $(patsubst %, $(SRC_DIR)/%, $(_SRC))
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))


all: kruskal

lib: $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

kruskal: lib
	$(CC) $(CFLAGS) kruskal.c $(OBJ) -o kruskal

comp_to_root: lib
	$(CC) $(CFLAGS) kruskal.c $(OBJ) -o ../kr && make clean

clean:
	rm -f $(OBJ_DIR)/*.o kruskal