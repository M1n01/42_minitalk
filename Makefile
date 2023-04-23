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

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

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