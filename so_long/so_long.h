/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:47 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/07 14:44:49 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <X11/keysym.h>
# include "./libft/libft.h"

typedef struct s_mlx
{
	void	*con;
	void	*wp;
	void	*sf;
	void	*muro;
	void	*play;
	void	*p_up;
	void	*p_sx;
	void	*coll;
	void	*exit;
	void	*enemy;
	void	*en_mov;
	int		en_fram;
	int		count_moves;
	int		direction;
}			t_mlx;

typedef struct s_map
{
	char			**matrix;
	char			**dup_matrix;
	char			*line;
	char			*arg;
	int				count_line;
	int				line_len;
	int				count_c;
	int				count_p;
	int				count_e;
	int				different_to_0;
	int				x_p;
	int				y_p;
	int				x_e;
	int				y_e;
	struct s_mlx	*mlx;
}			t_map;

int		ft_count_line(t_map *map);
int		ft_check_len_line(int len_line1, int count_line, t_map *map);
int		ft_check_elements(t_map *map);
int		ft_parsing(t_map *map);
int		ft_check_y(t_map *map);
int		ft_check_x(t_map *map);
int		ft_check_the_dup(t_map *map);
int		ft_create_window(t_map *map);
int		close_window(void *map);
int		ft_check_ber(char *argv);
int		ft_fillmatrix(t_map *map);
int		move_player(t_map *map, int new_y, int new_x, int direction);
int		ft_create_image(t_mlx *mlx);
int		count_moves(t_map *map);
int		animate_enemy(t_map *map);
void	flood_fill(t_map *map, int y_p, int x_p, char replace);
void	ft_free_matrix(char **matrix);
void	ft_space_saver(t_map *map);
void	ft_free_matrix(char **matrix);
void	ft_dup_matrix(t_map *map);
void	flood_fill(t_map *map, int y, int x, char replace);
void	ft_draw(t_mlx *mlx, t_map *map);
void	free_image(t_mlx *mlx);
void	ft_draw_background(t_mlx *mlx, t_map *map);
void	ft_draw_checkp(int x, int y, t_mlx *mlx);
void	ft_spawn_p_in_e(t_map *map, int new_y, int new_x, int direction);
char	**ft_fill_matrix(t_map *map);

#endif
