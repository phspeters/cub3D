# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 10:47:08 by pehenri2          #+#    #+#              #
#    Updated: 2024/07/14 12:49:43 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3d
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG) #-fsanitize=address
FLAG 		?= 	-Ofast
CC			= 	cc
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft
HEADERS		= 	-I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= 	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
FILES		= 	main.c \
				draw.c \
				hooks.c \
				utils.c

VPATH 		= 	./src:./src/mandatory
OBJS		= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= 	obj
EXE			?= 	cub3d

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT) --silent

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@make -C $(LIBFT) clean --silent

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean --silent

re: fclean all

val: all
	valgrind --leak-check=full --suppressions=MLX42_suppressions ./$(EXE) maps/default.cub

norm:
	@norminette $(SRCS_PATH) include $(LIBFT)

.PHONY: all, clean, fclean, re, norm, val