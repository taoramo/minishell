# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 14:48:17 by hpatsi            #+#    #+#              #
#    Updated: 2024/01/29 14:50:23 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

LIBFT = ../libft/libft.a

SOURCES = test.c \
		  $(addprefix ./commands/, extract_files.c split_command.c add_path.c \
		  						   run_command.c pipex.c pipe_commands.c)

OBJECTS = $(SOURCES:.c=.o)

INCLUDES_DIR = ./includes/

CFLAGS += -Wall -Wextra -Werror -Wunreachable-code -Wpedantic -Wtype-limits -I $(INCLUDES_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C ../libft/

clean:
	make clean -C ../libft/
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(PIPEX)

re: fclean all

readline:
	cc readline.c ../libft/libft.a -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

