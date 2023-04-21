NAME = $(SERVER) $(CLIENT)
SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFTDIR = ./libft
LIB = ./libft/libft.a
LIBFTINC = $(shell find $(LIBFTDIR) -name "*.h" -type f | xargs)
LIBFT = $(shell find $(LIBFTDIR) -name "*.c" -type f | xargs)

INC = ./include/minitalk.h

SERVER_SRC = ./src/server.c
SERVER_OBJ = $(SERVER_SRC:%.c=%.o)

CLIENT_SRC = ./src/client.c
CLIENT_OBJ = $(CLIENT_SRC:%.c=%.o)

ifdef WITH_BONUS
	SERVER_SRC = ./bonus/server_bonus.c
	CLIENT_SRC = ./bonus/client_bonus.c
endif

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

bonus:
		$(MAKE) WITH_BONUS=1

$(SERVER): $(SERVER_OBJ)
		$(MAKE) -C $(LIBFTDIR)
		$(CC) $(CFLAGS) $(addprefix -I,$(INC)) $(SERVER_SRC) $(LIB) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ)
		$(MAKE) -C $(LIBFTDIR)
		$(CC) $(CFLAGS) $(addprefix -I,$(INC)) $(CLIENT_SRC) $(LIB) -o $(CLIENT)

clean:
		$(MAKE) clean -C $(LIBFTDIR)
		$(RM) $(OBJS) $(SERVER_OBJ) $(CLIENT_OBJ) $(B_SERVER_OBJ) $(B_CLIENT_OBJ)

fclean: clean
		$(RM) $(SERVER) $(CLIENT)

re: fclean all

debug: CFLAGS += -g
debug: re

norm:
		@norminette -R CheckDefine $(INC) $(LIBFTINC)
		@norminette -R CheckForbiddenSourceHeader $(SERVER_SRC) $(CLIENT_SRC) ./bonus/server_bonus.c ./bonus/client_bonus.c

.PHONY: all clean fclean re bonus norm debug server client
