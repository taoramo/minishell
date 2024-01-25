NAME = minishell
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Wpedantic -Wtype-limits -g3
HEADERS = include/minishell.h
LIBS = $(LIBFT)
SRCS = main.c parse_parentheses.c expand_supergroups.c minishell_vec_utils.c ft_is_inside.c signal.c error.c handle_pipelines.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a
READLINE_TAAVI = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
READLINE = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(READLINE) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C ./libft/

clean:
	rm -rf $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft/

re: fclean all

taavi: $(OBJS) $(LIBFT)
	$(CC) $(READLINE_TAAVI) $(OBJS) $(LIBS) -o $(NAME)

.PHONY: all, clean, fclean, re
