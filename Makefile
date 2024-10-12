# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 10:47:08 by pehenri2          #+#    #+#              #
#    Updated: 2024/10/12 16:01:29 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	cub3d
CFLAGS		=	-Wextra -Wall -Werror -Wunreachable-code $(FLAG) #-fsanitize=address
FLAG 		?= 	-g3
CC			= 	cc
LIBMLX		= 	./lib/MLX42
LIBFT		= 	./lib/libft
HEADERS		= 	-I ./include -I $(LIBFT)
LIBS		= 	$(LIBFT)/libft.a
FILES		= 	main.c \
				parsing/parsing.c \
				parsing/check_file.c

VPATH 		= 	./src:./src/mandatory/
OBJS		= 	$(FILES:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR		= 	obj
EXE			?= 	cub3d

SUPP_FILE	= MLX42.suppressions

all: libft $(NAME)

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
	@make -C $(LIBFT) clean --silent

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean --silent

re: fclean all

val: all supp
	valgrind --leak-check=full --track-origins=yes --suppressions=$(SUPP_FILE) ./$(EXE) maps/default.cub

norm:
	@norminette src include $(LIBFT)

supp:
	echo "{" > $(SUPP_FILE)
	echo "   <MLX_CODAM>"  $(SUPP_FILE)
	echo "   Memcheck:Leak"  $(SUPP_FILE)
	echo "   match-leak-kinds: reachable"  $(SUPP_FILE)
	echo "   ..."  $(SUPP_FILE)
	echo "   fun:_dl_catch_exception"  $(SUPP_FILE)
	echo "   ..."  $(SUPP_FILE)
	echo "}"  $(SUPP_FILE)
	echo "{"  $(SUPP_FILE)
	echo " <MLX_CODAM>"  $(SUPP_FILE)
	echo "   Memcheck:Leak" >> $(SUPP_FILE)
	echo "   match-leak-kinds: reachable" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "   fun:mlx_init" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "}" >> $(SUPP_FILE)
	echo "{" >> $(SUPP_FILE)
	echo " <MLX_CODAM>" >> $(SUPP_FILE)
	echo "   Memcheck:Leak" >> $(SUPP_FILE)
	echo "   match-leak-kinds: reachable" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "   fun:XrmGetStringDatabase" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "}" >> $(SUPP_FILE)
	echo "{" >> $(SUPP_FILE)
	echo " <MLX_CODAM>" >> $(SUPP_FILE)
	echo "   Memcheck:Leak" >> $(SUPP_FILE)
	echo "   match-leak-kinds: reachable" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "   fun:_XrmInitParseInfo" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "}" >> $(SUPP_FILE)
	echo "{" >> $(SUPP_FILE)
	echo " <MLX_CODAM>" >> $(SUPP_FILE)
	echo "   Memcheck:Leak" >> $(SUPP_FILE)
	echo "   match-leak-kinds: reachable" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "   fun:__tls_get_addr" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "}" >> $(SUPP_FILE)
	echo "{" >> $(SUPP_FILE)
	echo " <MLX_CODAM>" >> $(SUPP_FILE)
	echo "   Memcheck:Leak" >> $(SUPP_FILE)
	echo "   match-leak-kinds: reachable" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "   fun:__pthread_once_slow" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "}" >> $(SUPP_FILE)
	echo "{" >> $(SUPP_FILE)
	echo " <MLX_CODAM>" >> $(SUPP_FILE)
	echo "   Memcheck:Leak" >> $(SUPP_FILE)
	echo "   match-leak-kinds: reachable" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "   fun:_dl_init" >> $(SUPP_FILE)
	echo "   ..." >> $(SUPP_FILE)
	echo "}" >> $(SUPP_FILE)

.PHONY: all, clean, fclean, re, norm, val