# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 14:16:45 by gpirozzi          #+#    #+#              #
#    Updated: 2025/02/05 12:33:18 by gpirozzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = so_long
SRC = parsing.c check_the_map.c check_P_E_C.c flood_fill.c mlx_graphic.c mlx_moves.c free_all.c draw.c


OBJ_SRC= ${SRC:.c=.o}

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIB_DIR = ./minilibx-linux
MINILIB = $(MINILIB_DIR)/libmlx.a
all: $(LIBFT) $(MINILIB) $(NAME)

$(LIBFT):
		@$(MAKE) -C $(LIBFT_DIR)

$(MINILIB):
		@$(MAKE) -C $(MINILIB_DIR)

$(NAME): $(OBJ_SRC) $(LIBFT) $(MINILIB)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MINILIB_DIR) $(OBJ_SRC) -L$(LIBFT_DIR) -lft -L$(MINILIB_DIR) -lmlx -lX11 -lXext -o $(NAME)

%.o: %.c
		@${CC} -c ${CFLAGS} -I$(LIBFT_DIR) $< -o $@

clean:
		rm -rf $(OBJ_SRC)
		@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
		rm -rf $(NAME)
		@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
