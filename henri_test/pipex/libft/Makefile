# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 08:42:34 by hpatsi            #+#    #+#              #
#    Updated: 2023/11/07 09:09:44 by hpatsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SOURCES = $(addprefix ./type/, ft_isalnum.c ft_isalpha.c ft_isascii.c \
							   ft_isdigit.c ft_isprint.c ft_isspace.c) \
	$(addprefix ./mem/, ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c \
						ft_memcpy.c ft_memmove.c ft_memset.c) \
	$(addprefix ./str/, ft_strchr.c ft_strcmp.c ft_strdup.c ft_striteri.c \
						ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
						ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
						ft_strtrim.c ft_substr.c ft_split.c) \
	$(addprefix ./put/, ft_putaddr_fd.c ft_putchar_fd.c ft_putendl_fd.c \
						ft_puthex_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
						ft_putunbr_fd.c) \
	$(addprefix ./conv/, ft_atoi.c ft_atol.c ft_itoa.c ft_tolower.c \
						 ft_toupper.c) \
	$(addprefix ./lst/, ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
						ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
						ft_lstnew.c ft_lstsize.c) \
	$(addprefix ./ft_printf/, ft_printf.c ft_printf_strutils.c \
							  ft_printf_nbrutils.c ft_printf_hexutils.c) \
	$(addprefix ./get_next_line/, get_next_line.c get_next_line_utils.c)

OBJECTS = $(SOURCES:.c=.o)

INCLUDES_DIR = ../includes/

CFLAGS += -Wall -Wextra -Werror -I $(INCLUDES_DIR)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rc $(NAME) $(OBJECTS)

$(OBJECTS): $(SOURCES)

bonus:
	echo "useless bonus rule for tests"

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests: $(NAME)
	cc $(CFLAGS) tests.c $(NAME) -I $(INCLUDES_DIR) -o test.out
	./test.out
	rm -f test.out