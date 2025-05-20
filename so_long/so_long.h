/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:47 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:35:04 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <X11/keysym.h>
# include "./libft/libft.h"

/*
** Struct to manage MLX graphical elements and game state
*/
typedef struct s_mlx
{
	void	*con;         // MLX connection context
	void	*wp;          // Window pointer
	void	*sf;          // Background sprite
	void	*muro;        // Wall sprite
	void	*play;        // Player sprite (front)
	void	*p_up;        // Player sprite (up)
	void	*p_sx;        // Player sprite (left)
	void	*coll;        // Collectible sprite
	void	*exit;        // Exit sprite
	void	*enemy;       // Static enemy sprite
	void	*en_mov;      // Animated enemy sprite
	int		en_fram;      // Animation frame counter
	int		count_moves;  // Number of player moves
	int		direction;    // Player direction (0: up, 1: down, 2: left, 3: right)
}	t_mlx;

/*
** Struct to represent the game map and its metadata
*/
typedef struct s_map
{
	char		**matrix;         // Original map matrix
	char		**dup_matrix;     // Duplicate used for flood fill
	char		*line;            // Temporary line buffer during parsing
	char		*arg;             // Argument path (e.g., .ber file)
	int			count_line;       // Number of lines in the map
	int			line_len;         // Length of each line
	int			count_c;          // Number of collectibles
	int			count_p;          // Number of player spawns
	int			count_e;          // Number of exits
	int			different_to_0;   // Validation counter for non-standard chars
	int			x_p;              // Player X position
	int			y_p;              // Player Y position
	int			x_e;              // Exit X position
	int			y_e;              // Exit Y position
	t_mlx		*mlx;             // Pointer to graphics and state structure
}	t_map;

int		ft_parsing(t_map *map);
int		ft_check_ber(char *argv);
int		ft_check_x(t_map *map);
int		ft_check_y(t_map *map);
int		ft_check_elements(t_map *map);
int		ft_check_len_line(int len_line1, int count_line, t_map *map);
int		ft_check_the_dup(t_map *map);
int		ft_count_line(t_map *map);

char	**ft_fill_matrix(t_map *map);
void	ft_duplicate_matrix(t_map *map);
void	flood_fill(t_map *map, int y, int x, char replace);
void	ft_free_matrix(char **matrix);

int		ft_create_window(t_map *map);
int		ft_create_image(t_mlx *mlx);
void	free_image(t_mlx *mlx);
int		close_window(void *map);

int		move_player(t_map *map, int new_y, int new_x, int direction);
void	ft_spawn_p_in_e(t_map *map, int new_y, int new_x, int direction);

void	ft_draw(t_mlx *mlx, t_map *map);
void	ft_draw_background(t_mlx *mlx, t_map *map);
void	ft_draw_checkp(int x, int y, t_mlx *mlx);

int		animate_enemy(t_map *map);
int		count_moves(t_map *map);

#endif

