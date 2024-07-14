# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 16:51:34 by pehenri2          #+#    #+#              #
#    Updated: 2023/11/21 13:06:51 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FILES = ft_isalpha.c			ft_isdigit.c			ft_isalnum.c			ft_isascii.c			ft_isprint.c		\
		ft_strlen.c				ft_memset.c				ft_bzero.c				ft_memcpy.c				ft_memmove.c		\
		ft_strlcpy.c			ft_strlcat.c			ft_toupper.c			ft_tolower.c			ft_strchr.c			\
		ft_strrchr.c			ft_strncmp.c			ft_memchr.c				ft_memcmp.c				ft_strnstr.c		\
		ft_atoi.c				ft_calloc.c				ft_strdup.c				ft_substr.c				ft_strjoin.c		\
		ft_strtrim.c			ft_split.c				ft_itoa.c				ft_strmapi.c			ft_striteri.c		\
		ft_putchar_fd.c			ft_putstr_fd.c			ft_putendl_fd.c			ft_putnbr_fd.c								\
																															\
		ft_lstnew.c				ft_lstadd_front.c		ft_lstsize.c			ft_lstlast.c			ft_lstadd_back.c	\
		ft_lstdelone.c			ft_lstclear.c			ft_lstiter.c			ft_lstmap.c									\
																															\
		ft_isspace.c    		ft_issign.c				ft_putnbr_base_fd.c		ft_count_words.c		ft_nbrlen.c			\
		ft_putptr_fd.c			ft_free_ptr_array.c		ft_free_str_array.c		ft_strtoupper.c			ft_strtolower.c		\
		ft_atoi_base.c			ft_free_str.c			ft_fprintf.c																				\
																															\
		ft_get_next_line.c		ft_printf.c
OBJ = $(FILES:.c=.o)
CC = cc
FLAGS = -Wall -Werror -Wextra -Ofast

all: $(NAME)

$(NAME): $(OBJ)

%.o: %.c
	@$(CC) $(FLAGS) -I . -c $< -o $@ && printf "Compiling: $(notdir $<\n)"
	@ar rcs $(NAME) $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
