CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = minitalk

SERVER = server
CLIENT = client

SRCDIR = ./src

SERVER_SRC = $(SRCDIR)/server.c
SERVER_OBJ = $(SERVER_SRC:%.c=%.o)

CLIENT_SRC = $(SRCDIR)/client.c
CLIENT_OBJ = $(CLIENT_SRC:%.c=%.o)

INCDIR = ./include
INC = $(INCDIR)/minitalk.h

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a

ifdef WITH_BONUS
	SERVER_SRC = ./bonus/server_bonus.c
	CLIENT_SRC = ./bonus/client_bonus.c
endif

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

bonus:
		$(MAKE) WITH_BONUS=1

$(SERVER): $(SERVER_OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -o $(SERVER) $(addprefix -I,$(INC))  $(SERVER_OBJ) $(LIBFT)

$(CLIENT): $(CLIENT_OBJ) $(LIBFT)
		$(CC) $(CFLAGS) -o $(CLIENT) $(addprefix -I,$(INC))  $(CLIENT_OBJ) $(LIBFT)

$(LIBFT):
		$(MAKE) -C $(LIBFTDIR)

clean:
		$(MAKE) fclean -C $(LIBFTDIR)
		$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
		$(RM) $(SERVER) $(CLIENT)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug bonus