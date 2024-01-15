NAME = minishell
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Wpedantic -Wtype-limits -o3
HEADERS = -I ./include
LIBS = $(LIBFT) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
SRCS = input.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C ./libft/

clean:
	rm -rf $(OBJS)
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re
