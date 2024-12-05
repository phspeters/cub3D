# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 10:47:08 by pehenri2          #+#    #+#              #
#    Updated: 2024/12/05 19:44:14 by pehenri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3D
BONUS_NAME	= 	cub3D_bonus
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG) #-fsanitize=address
FLAG 		?= 	-g3
CC			= 	cc

HEADERS		= 	-I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS		= 	$(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)/libft.a
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft

FILES		= 	main.c \
				player_movement.c \
				player_rotation.c \
				draw_scene.c \
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

BONUS_FILES	 =	main_bonus.c \
				player_action_bonus.c \
				player_movement_bonus.c \
				player_rotation_bonus.c \
				draw_line_bonus.c \
				draw_minimap_bonus.c \
				draw_scene_bonus.c \
				draw_sprites_bonus.c \
				draw_sprites_utils_bonus.c \
				draw_vertical_screen_line_bonus.c \
				raycasting_bonus.c \
				game_bonus.c \
				hooks_bonus.c \
				init_params_bonus.c \
				load_params_bonus.c \
				allocate_map_bonus.c \
				identification_bonus.c \
				parsing_bonus.c \
				error_bonus.c \
				utils_bonus.c \
				validate_arguments_bonus.c \
				validate_map_bonus.c \
				validate_rgb_bonus.c \
				validate_textures_bonus.c


VPATH 			= 	$(shell find src -type d | tr '\n' ':')
OBJS			= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS		= 	$(BONUS_FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR			= 	obj

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
	@printf "\n$(NAME) compiled successfully\n\n"
	@printf "CONTROLS:\n\
	W,A,S,D: move player\n\
	LEFT and RIGHT ARROWS: rotate player\n\
	ESC: exit game\n\n"

bonus: $(BONUS_OBJS) libmlx libft
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(BONUS_NAME)
	@printf "\n$(BONUS_NAME) compiled successfully\n\n"
	@printf "CONTROLS:\n\
	W,A,S,D: move player\n\
	LEFT and RIGHT ARROWS: rotate player\n\
	SPACE or LEFT MOUSE BUTTON: perform action\n\
	RIGHT MOUSE BUTTON: activate mouse rotation\n\
	M: toggle minimap\n\
	ESC: exit game\n\n"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX)/build
	@rm -rf $(SUPP_FILE)
	@make -C $(LIBFT) clean --silent

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)
	@rm -rf $(SUPP_FILE)
	@make -C $(LIBFT) fclean --silent

re: fclean all

INVALID_MAPS := $(wildcard maps/invalid/*.cub)
invalid: all
	@for map in $(INVALID_MAPS); do \
		printf "\nRunning ./$(NAME) $$map\n"; \
		./$(NAME) $$map || true; \
	done

b_invalid: all
	@for map in $(INVALID_MAPS); do \
		printf "\nRunning ./$(BONUS_NAME) $$map\n"; \
		./$(BONUS_NAME) $$map || true; \
	done

val_invalid: all supp
	@for map in $(INVALID_MAPS); do \
		printf "\nTesting $$map with valgrind\n"; \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=$(SUPP_FILE) \
		--error-exitcode=1 --quiet ./$(NAME) $$map || true; \
	done

b_val_invalid: all supp
	@for map in $(INVALID_MAPS); do \
		printf "\nTesting $$map with valgrind\n"; \
		valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --suppressions=$(SUPP_FILE) \
		--error-exitcode=1 --quiet ./$(BONUS_NAME) $$map || true; \
	done

#make val MAP=maps/valid/all_black.cub
val: all supp
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP_FILE) ./$(NAME) $(MAP)

#make val MAP=maps/valid/all_black.cub
b_val: all supp
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(SUPP_FILE) ./$(BONUS_NAME) $(MAP)

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
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:_dlerror_run" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
		echo "   Memcheck:Leak" >> $(SUPP_FILE); \
		echo "   match-leak-kinds: reachable" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "   fun:_dl_open" >> $(SUPP_FILE); \
		echo "   ..." >> $(SUPP_FILE); \
		echo "}" >> $(SUPP_FILE); \
		echo "{" >> $(SUPP_FILE); \
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
	fi

.PHONY: all, clean, fclean, re, norm, val