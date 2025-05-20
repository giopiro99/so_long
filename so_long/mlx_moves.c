/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_moves.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:33 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:06:51 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Moves the player to a new position on the map.
 *
 * Checks collisions with walls ('1') and enemies ('M').
 * Collects collectibles ('C') and decreases their count.
 * If the player reaches the exit ('E') with all collectibles gathered, triggers win.
 * Updates player's position and redraws the map.
 *
 * @param map Pointer to the map structure.
 * @param new_y New Y coordinate for the player.
 * @param new_x New X coordinate for the player.
 * @param direction Direction the player is facing (0=up, 1=down, 2=left, 3=right).
 * @return int Returns 0 on successful move, -1 if the player loses or wins (ends game).
 */
int	move_player(t_map *map, int new_y, int new_x, int direction)
{
	if (map->matrix[new_y][new_x] == '1')
		return (0);
	if (map->matrix[new_y][new_x] == 'M')
		return (ft_printf(1, "HAI PERSO!!"), close_window((void *)map), -1);
	if (map->matrix[new_y][new_x] == 'C')
	{
		map->matrix[new_y][new_x] = '0';
		map->count_c--;
	}
	if (map->matrix[new_y][new_x] == 'E' && map->count_c == 0)
		return (ft_printf(1, "HAI VINTO!!"), close_window((void *)map), -1);
	if (map->matrix[map->y_p][map->x_p] != 'E')
	{
		map->matrix[map->y_p][map->x_p] = '0';
		map->mlx->count_moves++;
	}
	map->y_p = new_y;
	map->x_p = new_x;
	if (map->matrix[new_y][new_x] != 'E')
		map->matrix[new_y][new_x] = 'P';
	ft_printf(1, "count moves:%d\n", map->mlx->count_moves);
	ft_spawn_p_in_e(map, new_y, new_x, direction);
	ft_draw(map->mlx, map);
	return (0);
}

/**
 * @brief Handles the player sprite when standing on the exit tile.
 *
 * If the player is on the exit tile and collectibles remain, changes the tile to 'P'.
 * Updates the player's facing direction.
 *
 * @param map Pointer to the map structure.
 * @param new_y Y coordinate of the player.
 * @param new_x X coordinate of the player.
 * @param direction Player's direction.
 */
void	ft_spawn_p_in_e(t_map *map, int new_y, int new_x, int direction)
{
	if (map->matrix[new_y][new_x] == 'E' && map->count_c > 0)
		map->matrix[new_y][new_x] = 'P';
	map->mlx->direction = direction;
}

/**
 * @brief Displays the number of player moves on the game window.
 *
 * Converts the move count to a string and draws it at a fixed position.
 *
 * @param map Pointer to the map structure.
 * @return int Always returns 0.
 */
int	count_moves(t_map *map)
{
	char	*moves;

	moves = ft_itoa(map->mlx->count_moves);
	mlx_string_put(map->mlx->con, map->mlx->wp, 140, 15, 0x000000, moves);
	free(moves);
	return (0);
}

/**
 * @brief Draws the player sprite on the window according to direction.
 *
 * Uses different images for up, left, and right/down directions.
 *
 * @param x X coordinate on the map.
 * @param y Y coordinate on the map.
 * @param mlx Pointer to the mlx structure containing images and window context.
 */
void	ft_draw_checkp(int x, int y, t_mlx *mlx)
{
	if (mlx->direction == 0)
		mlx_put_image_to_window(mlx->con, mlx->wp, mlx->p_up, x * 48, y * 48);
	else if (mlx->direction == 1 || mlx->direction == 3)
		mlx_put_image_to_window(mlx->con, mlx->wp, mlx->play, x * 48, y * 48);
	else if (mlx->direction == 2)
		mlx_put_image_to_window(mlx->con, mlx->wp, mlx->p_sx, x * 48, y * 48);
}

/**
 * @brief Animates the enemy and refreshes the game display.
 *
 * Updates the animation frame counter, resets after 100 frames,
 * redraws the entire map and updates the moves counter.
 *
 * @param map Pointer to the map structure.
 * @return int Always returns 0.
 */
int	animate_enemy(t_map *map)
{
	map->mlx->en_fram++;
	if (map->mlx->en_fram >= 100)
		map->mlx->en_fram = 0;
	ft_draw(map->mlx, map);
	count_moves(map);
	return (0);
}
