MAKEFLAGS += --no-print-directory

SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

SRC_SERVER = server.c server_utils.c clear_inactive.c
SRC_CLIENT = client.c client_signal_handler.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	@echo "📚 Compiling libft library..."
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(SERVER): $(OBJ_SERVER)
	@echo "🖥️  Compiling server binary..."
	@$(CC) $(CFLAGS) -o $(SERVER) $(OBJ_SERVER) $(LIBFT) $(LIBFT_INC)

$(CLIENT): $(OBJ_CLIENT)
	@echo "📡 Compiling client binary..."
	@$(CC) $(CFLAGS) -o $(CLIENT) $(OBJ_CLIENT) $(LIBFT) $(LIBFT_INC)

%.o: %.c
	@echo "🔧 Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "🗑️  Removing binaries..."
	@$(RM) $(SERVER) $(CLIENT)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
	@echo "🔄 Rebuilding everything..."

.PHONY: all clean fclean re

