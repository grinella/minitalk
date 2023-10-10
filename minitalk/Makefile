# Nome degli eseguibili
CLIENT = client
SERVER = server

# Compilatore e opzioni di compilazione
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directory dei sorgenti e degli oggetti
SRC_DIR = src
OBJ_DIR = obj

# File sorgenti per il client e il server
CLIENT_SRC = $(SRC_DIR)/client.c
SERVER_SRC = $(SRC_DIR)/server.c

# File oggetto generati dal compilatore
CLIENT_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(CLIENT_SRC))
SERVER_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SERVER_SRC))

# Obiettivi
all: $(CLIENT) $(SERVER)

# Eseguibili
$(CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regole per la compilazione
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Pulizia dei file oggetto e degli eseguibili
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

# Ricostruzione del progetto
re: fclean all

.PHONY: all clean fclean re
