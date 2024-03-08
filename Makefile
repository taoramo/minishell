NAME = minishell

LIBFT = ./libft/libft.a

READLINE = -lreadline -L ~/.brew/opt/readline/lib

LIBS = $(LIBFT) $(READLINE)

INCLUDES = -I ~/.brew/opt/readline/include -I ./includes/ -I./libft/

SRCS = $(addprefix srcs/, $(addprefix shell/, main.c parse_parentheses.c expand_supergroups.c minishell_vec_utils.c minishell_vec_utils2.c ft_is_inside.c signal.c signal2.c error.c error2.c handle_pipelines.c syntax_parenth.c syntax_other.c syntax_andor.c here_doc.c here_doc_input.c) \
	   $(addprefix commands/, prepare_command.c ft_isspace.c extract_files.c split_command.c isolate_redirects.c split_expanded_command.c find_command.c add_path.c run_command.c pipex.c pipe_commands.c pipe_commands2.c run_builtin.c builtin_fds.c ft_split_pipe.c calculate_exit.c) \
	   $(addprefix builtins/, builtins.c builtins2.c export.c export_utils.c cd.c) \
	   $(addprefix expand/, expand_envs.c expand_envs2.c wildcard.c wildcard2.c wildcard3.c wildcard4.c remove_quotes.c))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Wpedantic -Wtype-limits $(INCLUDES)

all: $(NAME)

$(OBJS): $(SRCS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) $(CFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft/

clean:
	rm -rf $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re
