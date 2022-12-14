NAME = $(SERVER) $(CLIENT)
SERVER = server
CLIENT = client

CC = cc
UTILSDIR = ./utils

CFLAGS = -Wall -Wextra -Werror

INC = ./include/minitalk.h
B_INC = ./include/minitalk_bonus.h
UTILSINC = $(shell find $(UTILSDIR) -name "*.h" -type f | xargs)
SERVER_SRC = ./src/server.c
CLIENT_SRC = ./src/client.c
UTILS = $(shell find $(UTILSDIR) -name "*.c" -type f | xargs)
LIB = ./utils/libftprintf.a

SERVER_OBJ = $(SERVER_SRC:%.c=%.o)
CLIENT_OBJ = $(CLIENT_SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
		$(MAKE) -C ./utils
		$(CC) $(CFLAGS) $(addprefix -I,$(INC)) $(SERVER_SRC) $(LIB) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ)
		$(MAKE) -C ./utils
		$(CC) $(CFLAGS) $(addprefix -I,$(INC)) $(CLIENT_SRC) $(LIB) -o $(CLIENT)

clean:
		$(RM) $(OBJS) $(SERVER_OBJ) $(CLIENT_OBJ) $(B_SERVER_OBJ) $(B_CLIENT_OBJ) $(UTILS_OBJ)

fclean: clean
		$(RM) $(SERVER) $(CLIENT)

re: fclean all

debug: CFLAGS += -g -fsanitize=address,leak
debug: re

norm:
		@norminette -R CheckDefine $(INC) $(UTILSINC)
		@norminette -R CheckForbiddenSourceHeader $(SERVER_SRC) $(CLIENT_SRC) $(UTILS)

.PHONY: all clean fclean re bonus norm debug server client
