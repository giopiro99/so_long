/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:15 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:03:58 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Creates a duplicate of the map matrix in the map structure.
 *
 * Allocates memory for dup_matrix and copies each string from the original matrix.
 * Used to manipulate the map copy without altering the original.
 *
 * @param map Pointer to the map structure containing the original matrix and where dup_matrix is stored.
 */
void	ft_duplicate_matrix(t_map *map)
{
	int	i;

	i = 0;
	map->dup_matrix = malloc(sizeof(char *) * (map->count_line + 1));
	if (!map->dup_matrix)
	{
		free(map->dup_matrix);
		return ;
	}
	while (map->matrix[i] != NULL)
	{
		map->dup_matrix[i] = ft_strdup(map->matrix[i]);
		if (!map->dup_matrix)
			return (free(map->dup_matrix));
		i++;
	}
	map->dup_matrix[i] = NULL;
}

/**
 * @brief Recursively fills reachable areas in the duplicate map matrix starting from coordinates (y, x).
 *
 * This flood fill replaces all walkable tiles (not '1' or 'M') with the 'replace' character,
 * marking them as visited or blocked. Used to verify path accessibility.
 *
 * @param map Pointer to the map structure containing the dup_matrix.
 * @param y Current row index in the matrix.
 * @param x Current column index in the matrix.
 * @param replace Character to mark the visited positions in dup_matrix.
 */
void	flood_fill(t_map *map, int y, int x, char replace)
{
	if (y < 0 || y > map->count_line)
		return ;
	if (x < 0 || x > map->line_len)
		return ;
	if (map->dup_matrix[y][x] == '1' || map->dup_matrix[y][x] == 'M')
		return ;
	map->dup_matrix[y][x] = replace;
	flood_fill(map, y + 1, x, '1');
	flood_fill(map, y - 1, x, '1');
	flood_fill(map, y, x + 1, '1');
	flood_fill(map, y, x - 1, '1');
	return ;
}

/**
 * @brief Checks if there are unreachable exits ('E') or collectibles ('C') in the duplicated map matrix.
 *
 * Scans dup_matrix for any remaining 'E' or 'C' after flood fill.
 * Returns error if any are found, indicating that they are not reachable.
 *
 * @param map Pointer to the map structure containing the dup_matrix.
 * @return int 0 if all reachable, -1 if unreachable elements found.
 */
int	ft_check_the_dup(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->dup_matrix[i] != NULL)
	{
		while (map-> dup_matrix[i][j] != '\0')
		{
			if (map->dup_matrix[i][j] == 'E')
				return (ft_printf(2, "Error\nE non e' raggiungibile"), -1);
			if (map->dup_matrix[i][j] == 'C')
				return (ft_printf(2, "Error\nC non raggiungibili"), -1);
			j++;
		}
		j = 0;
		i ++;
	}
	return (0);
}
