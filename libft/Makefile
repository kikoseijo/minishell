# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 23:24:18 by jseijo-p          #+#    #+#              #
#    Updated: 2022/11/14 13:05:24 by jseijo-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
HEAD := -I inc/

#CFLAGS = -fsanitize=address -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -g3
#CFLAGS = -fsanitize=address

SRCS	=	src/maths/ft_atoi.c \
				src/maths/ft_itoa.c \
				src/memory/ft_bzero.c \
				src/memory/ft_calloc.c \
				src/memory/ft_memchr.c \
				src/memory/ft_memcmp.c \
				src/memory/ft_memcpy.c \
				src/memory/ft_memmove.c \
				src/memory/ft_memset.c \
				src/print/ft_putchar_fd.c \
				src/print/ft_putstr_fd.c \
				src/print/ft_putnbr_fd.c \
				src/print/ft_putendl_fd.c \
				src/strings/ft_array_join.c \
				src/strings/ft_array_len.c \
				src/strings/ft_concat_char.c \
				src/strings/ft_strcmp.c \
				src/strings/ft_isalnum.c \
				src/strings/ft_isalpha.c \
				src/strings/ft_isascii.c \
		 		src/strings/ft_isdigit.c \
				src/strings/ft_strrchr.c \
				src/strings/ft_strdup.c \
				src/strings/ft_isprint.c \
				src/strings/ft_isset.c \
				src/strings/ft_free_array.c \
				src/strings/ft_split.c \
				src/strings/ft_str_is_numeric.c \
				src/strings/ft_strchr.c \
				src/strings/ft_strlen.c \
				src/strings/ft_strncmp.c \
				src/strings/ft_strnstr.c \
				src/strings/ft_tolower.c \
				src/strings/ft_toupper.c \
				src/strings/ft_strlcpy.c \
				src/strings/ft_strlcat.c \
				src/strings/ft_substr.c \
				src/strings/ft_strjoin.c \
				src/strings/ft_strtrim.c \
				src/strings/ft_strmapi.c \
				src/strings/ft_striteri.c \
				src/lists/ft_lstadd_front.c \
				src/lists/ft_lstsize.c \
				src/lists/ft_lstlast.c \
				src/lists/ft_lstadd_back.c \
				src/lists/ft_lstnew.c \
				src/lists/ft_lstdelone.c \
				src/lists/ft_lstclear.c \
				src/lists/ft_lstiter.c \
				src/lists/ft_lstmap.c \
				src/utils/ft_print_int.c \
				src/utils/ft_print_p.c \
				src/utils/ft_print_unint.c \
				src/utils/ft_print_x.c \
				src/utils/ft_printf.c \
				src/utils/get_next_line.c

#color
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

OBJS	=	$(addprefix objs/, $(SRCS:.c=.o))

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef

all: $(NAME)

$(NAME):	$(OBJS)
		@ar rcs $(NAME) $(OBJS)
		@echo ' '
		@echo '......( \_/ ) '
		@echo '......( o_o ) '
		@echo '..../""""""""""""\======░ ▒▓▓█D' "$(WARN_COLOR)\t$(NAME)\t $(OK_COLOR) [Happy coding]$(NO_COLOR)";
		@echo '/"""""""""""""""""""\ '
		@echo '\_@_@_@_@_@_@_@_@_@_/'
		@echo ' '

objs/%.o: %.c
	@mkdir -p $(dir $@)
	@$(call run_and_test,gcc $(CFLAGS) $(HEAD) -c $< -o $@)

clean:
		/bin/rm -f $(OBJS)
		@echo $(OBJS) cleaned.

fclean: clean
			rm -f $(NAME)
			@echo $(NAME) cleaned.

re:	fclean
	$(MAKE)

.PHONY: all, clean, fclean, re
