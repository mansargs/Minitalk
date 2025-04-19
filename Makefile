SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJ_SERVER) $(LIBFT) $(LIBFT_INC)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJ_CLIENT) $(LIBFT) $(LIBFT_INC)

clean:
	$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
