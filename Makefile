NAME = $(SERVER) $(CLIENT)
SERVER = server
CLIENT = client

CC = cc
INCDIR = ./include
UTILSDIR = ./utils
BONUSDIR = ./bonus

CFLAGS = -Wall -Wextra -Werror $(addprefix -I,$(INC))

INC = $(shell find $(INCDIR) -name "*.h" -type f | xargs)
UTILSINC = $(shell find $(UTILSDIR) -name "*.h" -type f | xargs)
SERVER_SRC = ./src/server.c
CLIENT_SRC = ./src/client.c
UTILS = $(shell find $(UTILSDIR) -name "*.c" -type f | xargs)
LIB = ./utils/libftprintf.a
B_SRCS = $(shell find $(BONUSDIR) -name "*_bonus.c" -type f | xargs)

SERVER_OBJ = $(SERVER_SRC:%.c=%.o)
CLIENT_OBJ = $(CLIENT_SRC:%.c=%.o)
B_OBJS = $(B_SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(SERVER) $(CLIENT)

$(SERVER): $(SERVER_OBJ)
		$(MAKE) -C ./utils
		$(CC) $(CFLAGS) $(SERVER_SRC) $(LIB) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ)
		$(MAKE) -C ./utils
		$(CC) $(CFLAGS) $(CLIENT_SRC) $(LIB) -o $(CLIENT)

bonus:
		@make all WITH_BONUS=1

clean:
		$(RM) $(OBJS) $(SERVER_OBJ) $(CLIENT_OBJ) $(B_OBJS) $(UTILS_OBJ)

fclean: clean
		$(RM) $(SERVER) $(CLIENT)

re: fclean all

debug: CFLAGS += -g -fsanitize=address,leak
debug: re

norm:
		@norminette -R CheckDefine $(INC) $(UTILSINC)
		@norminette -R CheckForbiddenSourceHeader $(SERVER_SRC) $(CLIENT_SRC) $(UTILS)

.PHONY: all clean fclean re bonus norm debug server client
