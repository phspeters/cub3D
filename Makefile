# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 10:47:08 by pehenri2          #+#    #+#              #
#    Updated: 2024/11/28 19:14:02 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3D
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG) #-fsanitize=address
FLAG 		?= 	-g3
CC			= 	cc

HEADERS		= 	-I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= 	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft

FILES		= 	main.c \
				player_action.c \
				player_movement.c \
				player_rotation.c \
				draw_line.c \
				draw_minimap.c \
				draw_scene.c \
				draw_sprites.c \
				draw_sprites_utils.c \
				draw_vertical_screen_line.c \
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

VPATH 		= 	$(shell find src -type d | tr '\n' ':')
OBJS		= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= 	obj

EXE			?= 	./cub3D
MAP			?= 	maps/valid/subject.cub
SUPP_FILE	= MLX42.suppressions

all: libmlx libft $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build >/dev/null 2>&1 && make -C $(LIBMLX)/build -j4 --silent

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

INVALID_MAPS := $(wildcard maps/invalid/*.cub)
invalid: all
	@for map in $(INVALID_MAPS); do \
		printf "\nRunning ./$(EXE) $$map\n"; \
		./$(EXE) $$map || true; \
	done

val_invalid: all supp
	@for map in $(INVALID_MAPS); do \
		printf "\nTesting $$map with valgrind\n"; \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=$(SUPP_FILE) \
		--error-exitcode=1 --quiet ./$(EXE) $$map || true; \
	done

#make val MAP=maps/valid/all_black.cub
#make val EXE=./cub3D_bonus MAP=maps/valid/all_black.cub
val: all supp
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP_FILE) $(EXE) $(MAP)

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