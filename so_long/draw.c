/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:51 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/26 17:58:49 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_background(t_mlx *mlx, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->count_line)
	{
		x = 0;
		while (x < map->line_len)
		{
			if (map->matrix[y][x] == '0'
				|| (map->matrix[y][x] == 'E' && map->count_c > 0))
				mlx_put_image_to_window(mlx->con, mlx->wp,
					mlx->sf, x * 48, y * 48);
			x++;
		}
		y++;
	}
}

void	ft_draw_checks(int y, int x, t_map *map, void *cur_en)
{
	if (map->matrix[y][x] == '1')
		mlx_put_image_to_window(map->mlx->con, map->mlx->wp,
			map->mlx->muro, x * 48, y * 48);
	if (map->matrix[y][x] == 'P')
		ft_draw_checkp(x, y, map->mlx);
	if (map->count_c == 0)
	{
		map->matrix[map->y_e][map->x_e] = 'E';
		mlx_put_image_to_window(map->mlx->con, map->mlx->wp, map->mlx->exit,
			map->x_e * 48, map->y_e * 48);
	}
	if (map->matrix[y][x] == 'C')
		mlx_put_image_to_window(map->mlx->con, map->mlx->wp,
			map->mlx->coll, x * 48, y * 48);
	if (map->matrix[y][x] == 'M')
		mlx_put_image_to_window(map->mlx->con, map->mlx->wp,
			cur_en, x * 48, y * 48);
	return ;
}

void	ft_draw(t_mlx *mlx, t_map *map)
{
	int		x;
	int		y;
	void	*current_enemy;

	x = 0;
	y = 0;
	if (mlx->en_fram >= 0 && mlx->en_fram <= 50)
		current_enemy = mlx->enemy;
	else if (mlx->en_fram > 50 && mlx->en_fram <= 100)
		current_enemy = mlx->en_mov;
	ft_draw_background(map->mlx, map);
	while (y < map->count_line)
	{
		x = 0;
		while (x < (map->line_len))
		{
			ft_draw_checks(y, x, map, current_enemy);
			x++;
		}
		y++;
	}
}

int	ft_create_image2(t_mlx *mlx)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	mlx->sf = mlx_xpm_file_to_image(mlx->con, "./i/S2.xpm", &width, &height);
	if (!mlx->sf)
		return (-1);
	mlx->muro = mlx_xpm_file_to_image(mlx->con, "./i/1.xpm", &width, &height);
	if (!mlx->muro)
		return (free_image(mlx), -1);
	mlx->play = mlx_xpm_file_to_image(mlx->con, "./i/P.xpm", &width, &height);
	if (!mlx->play)
		return (free_image(mlx), -1);
	mlx->coll = mlx_xpm_file_to_image(mlx->con, "./i/C.xpm", &width, &height);
	if (!mlx->coll)
		return (free_image(mlx), -1);
	mlx->en_mov = mlx_xpm_file_to_image(mlx->con, "./i/M_MOVE.xpm",
			&width, &height);
	if (!mlx->en_mov)
		return (free_image(mlx), -1);
	return (0);
}

int	ft_create_image(t_mlx *mlx)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	ft_create_image2(mlx);
	mlx->exit = mlx_xpm_file_to_image(mlx->con, "./i/E.xpm", &width, &height);
	if (!mlx->exit)
		return (free_image(mlx), -1);
	mlx->enemy = mlx_xpm_file_to_image(mlx->con, "./i/M.xpm", &width, &height);
	if (!mlx->enemy)
		return (free_image(mlx), -1);
	mlx->p_up = mlx_xpm_file_to_image(mlx->con, "./i/PUP.xpm", &width, &height);
	if (!mlx->p_up)
		return (free_image(mlx), -1);
	mlx->p_sx = mlx_xpm_file_to_image(mlx->con, "./i/PSX.xpm", &width, &height);
	if (!mlx->p_sx)
		return (free_image(mlx), -1);
	return (0);
}
