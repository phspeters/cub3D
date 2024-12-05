# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 10:47:08 by pehenri2          #+#    #+#              #
#    Updated: 2024/11/24 18:19:28 by roglopes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3D
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG) #-fsanitize=address
FLAG 		?= 	-g3
CC			= 	cc
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft
HEADERS		= 	-I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= 	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
FILES		= 	main.c \
				player_action.c \
				player_movement.c \
				draw_line.c \
				draw_minimap.c \
				draw_scene.c \
				draw_sprites.c \
				draw_sprites_utils.c \
				raycasting.c \
				game.c \
				hooks.c \
				init_params.c \
				load_params.c \
				allocate_map.c \
				identification.c \
				parsing.c \
				error.c \
				utils.c \
				validate_arguments.c \
				validate_map.c \
				validate_rgb.c \
				validate_textures.c

VPATH 		= 	./src:./src/actions:./src/drawing:./src/game:./src/parsing:./src/utils:./src/validation
OBJS		= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= 	obj
EXE			?= 	cub3D

SUPP_FILE	= MLX42.suppressions

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
	@rm -rf $(SUPP_FILE)
	@make -C $(LIBFT) clean --silent

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(SUPP_FILE)
	@make -C $(LIBFT) fclean --silent

re: fclean all

val: all supp
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP_FILE) ./$(EXE) maps/valid/spaced_info.cub

norm:
	@norminette src include $(LIBFT)

supp:
	@if [ ! -f $(SUPP_FILE) ]; then \
		echo "{" > $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:_dl_catch_exception" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:mlx_init" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:XrmGetStringDatabase" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:_XrmInitParseInfo" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:__tls_get_addr" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:__pthread_once_slow" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:_dl_init" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
	fi

.PHONY: all, clean, fclean, re, norm, val