# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 10:47:08 by pehenri2          #+#    #+#              #
#    Updated: 2024/11/11 15:45:55 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3d
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG) #-fsanitize=address
FLAG 		?= 	-g3
CC			= 	cc
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft
HEADERS		= 	-I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= 	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
FILES		= 	main.c \
				parsing/parsing.c \
				parsing/check_texture.c \
				parsing/check_file.c \
				parsing/check_rgb.c \
				parsing/calculate_allocate_map.c \
				parsing/process_map.c \
				parsing/check_map.c \
				debugging/debugging.c \
				draw_minimap.c \
				draw_scene.c \
				draw_sprites.c \
				draw_sprites_utils.c \
				game.c \
				hooks.c \
				init_params.c \
				load_params.c \
				load_textures.c \
				player_action.c \
				player_movement.c \
				raycasting.c \
				utils.c \
				draw_line.c \

VPATH 		= 	./src:./src/mandatory
OBJS		= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= 	obj
EXE			?= 	cub3d

SUPP_FILE	= MLX42.suppressions

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT) --silent

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC)  $(HEADERS) -c $< -o $@ && printf "Compiling: $(notdir $<\n)"

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP_FILE) ./$(EXE) maps/default.cub

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