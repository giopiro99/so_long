/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_P_E_C.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:16:59 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:01:17 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if the given filename has a ".ber" extension.
 *
 * Compares the last 4 characters of the string to ".ber".
 * Prints an error and returns -1 if the extension is not correct,
 * otherwise returns 0.
 *
 * @param argv The filename string to check.
 * @return int 0 if correct extension, -1 otherwise.
 */
int	ft_check_ber(char *argv)
{
	if (ft_strncmp(argv + (ft_strlen(argv) - 4), ".ber", 4) == 0)
		return (0);
	else
		return (ft_printf(2, "Error\nMappa non .ber"), -1);
}

/**
 * @brief Checks and counts map elements on a given row.
 *
 * Iterates over each character in the map row at index `i` and updates
 * the counts and positions of players ('P'), exits ('E'), collectibles ('C'),
 * and counts any invalid characters (not '1', '0', '\n', or 'M').
 *
 * @param i The index of the row in the map matrix.
 * @param map Pointer to the map structure holding counts and matrix.
 */
void	ft_check(int i, t_map *map)
{
	int	j;

	j = 0;
	while (map->matrix[i][j] != '\0')
	{
		if (map->matrix[i][j] == 'P')
		{
			map->count_p++;
			map->y_p = i;
			map->x_p = j;
		}
		else if (map->matrix[i][j] == 'E')
		{
			map->count_e++;
			map->y_e = i;
			map->x_e = j;
		}
		else if (map->matrix[i][j] == 'C')
			map->count_c++;
		else if (map->matrix[i][j] != '1' && map->matrix[i][j] != '0'
					&& map->matrix[i][j] != '\n' && map->matrix[i][j] != 'M')
			map->different_to_0++;
		j++;
	}
	return ;
}

/**
 * @brief Iterates over the entire map matrix and checks elements.
 *
 * Calls `ft_check` for each row in the map matrix to update counts of
 * players, exits, collectibles, and invalid characters.
 *
 * @param map Pointer to the map structure holding the matrix and counts.
 */
void	ft_space_saver(t_map *map)
{
	int	i;

	i = 0;
	while (map->matrix[i] != NULL)
	{
		ft_check(i, map);
		i++;
	}
}

/**
 * @brief Validates the counts of essential elements in the map.
 *
 * Ensures there is exactly one player, one exit, at least one collectible,
 * and no invalid characters. Frees the map matrix and returns error if
 * conditions are not met.
 *
 * @param map Pointer to the map structure with counts and matrix.
 * @return int 0 if map is valid, -1 if invalid.
 */
int	ft_check_elements(t_map *map)
{
	map->count_p = 0;
	map->count_e = 0;
	map->count_c = 0;
	map->different_to_0 = 0;
	ft_space_saver(map);
	if ((map->count_p != 1) || (map->count_e != 1)
		|| (map->count_c == 0) || (map->different_to_0 != 0))
	{
		ft_free_matrix(map->matrix);
		return (ft_printf(2, "Error\nerrore negli elementi della mappa"), -1);
	}
	return (0);
}
