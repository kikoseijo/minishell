# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/07 08:55:28 by jseijo-p          #+#    #+#              #
#    Updated: 2022/10/31 21:35:18 by cmac             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g

INC_LIBFT = -I libft
INCDIR	= ./inc/
INC_READLINE = -I ~/.brew/opt/readline/include
LINK_READLINE = -L ~/.brew/opt/readline/lib
INC_READLINE_K = -I /usr/local/opt/readline/include
LINK_READLINE_K = -L /usr/local/opt/readline/lib

SRC = src/minishell.c \
			src/exec/execute.c \
			src/exec/utils.c \
			src/builtin/ft_cd.c \
			src/builtin/ft_echo.c \
			src/builtin/ft_env.c \
			src/builtin/ft_exit.c \
			src/builtin/ft_export.c \
			src/builtin/ft_pwd.c \
			src/builtin/ft_unset.c \
			src/parser/parser.c \
			src/parser/parser_utils.c \
			src/parser/parser_utils2.c \
			src/env.c \
			src/parser/errors.c \
			src/parser/redirections_files.c \
			src/parser/quotes.c \
			src/parser/parser_utils3.c

# SRC_BONUS = pipex_bonus.c helpers.c

OBJ = $(SRC:.c=.o)
# OBJ_BONUS = $(SRC_BONUS:.c=.o)

CC := gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(CFLAGS) $(INC_LIBFT) -I $(INCDIR) $(INC_READLINE_K) $(LINK_READLINE_K) $(OBJ) ./libft/libft.a -lreadline -lncurses -o $(NAME)

clean:
	$(MAKE) -C libft fclean
	rm -f $(OBJ)
	echo $(NAME) objects files cleaned

fclean: clean
	rm -f $(NAME)
	echo $(NAME) cleaned

re: fclean $(MAKE) $(NAME)

norme:
	norminette -R CheckForbiddenSourceHeader ${wildcard src/*.c} ${wildcard src/**/*.c} ${wildcard inc/*.h} ${wildcard libft/src/**/*.c} ${wildcard libft/inc/*.h}

.PHONY: re, fclean, clean , all
