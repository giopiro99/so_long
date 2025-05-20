/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:33 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/18 14:56:21 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_player(t_map *map, int new_y, int new_x, int direction)
{
	if (map->matrix[new_y][new_x] == '1')
		return (0);
	if (map->matrix[new_y][new_x] == 'M')
		return (ft_printf("HAI PERSO!!"), close_window((void *)map), -1);
	if (map->matrix[new_y][new_x] == 'C')
	{
		map->matrix[new_y][new_x] = '0';
		map->count_c--;
	}
	if (map->matrix[new_y][new_x] == 'E' && map->count_c == 0)
		return (ft_printf("HAI VINTO!!"), close_window((void *)map), -1);
	if (map->matrix[map->y_p][map->x_p] != 'E')
	{
		map->matrix[map->y_p][map->x_p] = '0';
		map->mlx->count_moves++;
	}
	map->y_p = new_y;
	map->x_p = new_x;
	if (map->matrix[new_y][new_x] != 'E')
		map->matrix[new_y][new_x] = 'P';
	ft_printf("count moves:%d\n", map->mlx->count_moves);
	ft_spawn_p_in_e(map, new_y, new_x, direction);
	ft_draw(map->mlx, map);
	return (0);
}

void	ft_spawn_p_in_e(t_map *map, int new_y, int new_x, int direction)
{
	if (map->matrix[new_y][new_x] == 'E' && map->count_c > 0)
		map->matrix[new_y][new_x] = 'P';
	map->mlx->direction = direction;
}

int	count_moves(t_map *map)
{
	char	*moves;

	moves = ft_itoa(map->mlx->count_moves);
	mlx_string_put(map->mlx->con, map->mlx->wp, 140, 15, 0x000000, moves);
	free(moves);
	return (0);
}

void	ft_draw_checkp(int x, int y, t_mlx *mlx)
{
	if (mlx->direction == 0)
		mlx_put_image_to_window(mlx->con, mlx->wp, mlx->p_up, x * 48, y * 48);
	else if (mlx->direction == 1 || mlx->direction == 3)
		mlx_put_image_to_window(mlx->con, mlx->wp, mlx->play, x * 48, y * 48);
	else if (mlx->direction == 2)
		mlx_put_image_to_window(mlx->con, mlx->wp, mlx->p_sx, x * 48, y * 48);
}

int	animate_enemy(t_map *map)
{
	map->mlx->en_fram++;
	if (map->mlx->en_fram >= 100)
		map->mlx->en_fram = 0;
	ft_draw(map->mlx, map);
	count_moves(map);
	return (0);
}
