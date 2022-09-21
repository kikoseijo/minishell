# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 08:55:28 by jseijo-p          #+#    #+#              #
#    Updated: 2022/09/21 16:58:27 by jseijo-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g -Og

SRC = src/minishell.c \
			src/env.c \
			src/built_in.c \
			src/parser.c \
			src/parser_utils.c \
			src/parser_utils2.c \
			src/execute.c

# SRC_BONUS = pipex_bonus.c helpers.c

OBJ = $(SRC:.c=.o)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC := gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(FLAGS) -I libft $(OBJ) ./libft/libft.a -lreadline -lncurses -o $(NAME)

clean:
	$(MAKE) -C libft fclean
	rm -f $(OBJ)
	echo $(NAME) objects files cleaned

fclean: clean
	rm -f $(NAME)
	echo $(NAME) cleaned

re: fclean $(MAKE) $(NAME)

norme:
	norminette -R CheckForbiddenSourceHeader ${wildcard src/*.c} ${wildcard inc/*.h} ${wildcard libft/src/**/*.c} ${wildcard libft/inc/*.h}

.PHONY: re, fclean, clean , all
