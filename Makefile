# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviau <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/11 11:02:36 by aviau             #+#    #+#              #
#    Updated: 2016/11/20 06:37:47 by aviau            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=wolf3D

SRC_NAME =	draw_map.c\
			key.c\
			mouse.c\
			graphic.c\
			get_next_line.c\
			main.c\
			parse.c\
			trash.c\
			minimap.c

OBJ_NAME = $(SRC_NAME:.c=.o)
SRC_PATH = ./src/
OBJ_PATH = ./obj/
SRC=$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC=-I ./include -I./libft -I ./libmlx
ARG=-L ./libft -lft -lmlx\
	-framework OpenGl -framework AppKit
CFLAGS = -Wall -Wextra -Werror
DEPDIR				= .deps/
DEPFILES			= $(patsubst %.c,$(DEPDIR)%.d,$(SRC_NAME))

all: $(NAME)

# Auto dependency generator
$(DEPDIR)/%.d: $(SRC_PATH)%.c $(DEPDIR)%.d
	@mkdir -p $(DEPDIR)
	@$(CC) $(CFLAGS) $(INC) -MM -MT $(DEPDIR)$(patsubst %.c,$(DEPDIR)%.d,$(notdir $@)) $< -MF $@

# Add dependency as prerequisites
-include $(DEPFILES)

$(NAME): lib $(OBJ)
	@gcc -g -O0 $(CFLAGS) $(ARG) $(INC) $(OBJ) -o $@

lib:
	@make -C ./libft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	-@mkdir -p $(OBJ_PATH)
	@gcc $(CFLAGS) -c -o $@ $< $(INC)

clean:
	-@rm -rf $(OBJ_PATH) $(DEPDIR)
	@make -C ./libft $@

fclean: clean
	-@rm $(NAME)
	@make -C ./libft $@

re: fclean all

.PHONY: fclean clean
