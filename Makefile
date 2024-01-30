NAME = minishell

LIBFT = ./libft/libft.a

READLINE = -lreadline -L ~/.brew/opt/readline/lib
READLINE_TAAVI = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

LIBS = $(LIBFT) $(READLINE)

INCLUDES = -I ~/.brew/opt/readline/include -I ./includes/

SRCS = $(addprefix srcs/, $(addprefix shell/, main.c parse_parentheses.c expand_supergroups.c minishell_vec_utils.c ft_is_inside.c signal.c error.c handle_pipelines.c) \
	   $(addprefix commands/, extract_files.c here_doc.c split_command.c add_path.c run_command.c pipex.c pipe_commands.c))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Wpedantic -Wtype-limits -g3 $(INCLUDES)

all: $(NAME)

$(OBJS): $(SRCS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

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
	$(CC) $(READLINE_TAAVI) $(OBJS) $(LIBFT) -o $(NAME)

.PHONY: all, clean, fclean, re
