# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviau <aviau@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/09 02:00:53 by aviau             #+#    #+#              #
#    Updated: 2016/07/04 20:35:02 by aviau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_isascii.c ft_memchr.c ft_putchar.c ft_putstr.c ft_strcpy.c \
		ft_strjoin.c ft_strncmp.c ft_strsplit.c ft_isdigit.c ft_memcmp.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_strdel.c ft_strlcat.c ft_strncpy.c \
		ft_strstr.c ft_atoi.c ft_isprint.c ft_memcpy.c ft_putendl.c \
		ft_strcat.c	ft_strdup.c ft_strlen.c ft_strnequ.c ft_strsub.c \
		ft_bzero.c ft_itoa.c ft_memdel.c ft_putendl_fd.c ft_strchr.c \
		ft_strequ.c ft_strmap.c ft_strnew.c ft_strtrim.c ft_isalnum.c \
		ft_memalloc.c ft_memmove.c ft_putnbr.c ft_strclr.c ft_striter.c \
		ft_strmapi.c ft_strnstr.c ft_tolower.c ft_isalpha.c ft_memccpy.c \
		ft_memset.c ft_putnbr_fd.c ft_strcmp.c ft_striteri.c ft_strncat.c \
		ft_strrchr.c ft_toupper.c ft_lstadd.c ft_lstdelone.c ft_lstmap.c \
		ft_lstdel.c ft_lstiter.c ft_lstnew.c ft_sort.c ft_strblk.c \
		ft_disptab.c ft_power.c ft_square.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : ./libft.h $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o:%.c
	gcc -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
