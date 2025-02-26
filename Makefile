include Include.mk 
SRC_DIR = src
OBJ_DIR = build
CC = cc
LIBFT = libft
LINKERS= -L./$(LIBFT) -lft -L. -lreadline -lcurses
CFLAGS = -Wall -Werror -Wextra -I./includes -I./libft/includes -g
NAME = minishell
SRCSDIR=$(addprefix src/,$(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCSDIR))


all: libft $(NAME)

libft:
	@make -C $(LIBFT)
$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(OBJS) $(LINKERS) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
clean: 
	@make -C $(LIBFT) fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
