/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:07 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:02:14 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Reads the map file and fills the map matrix with trimmed lines.
 *
 * Opens the file at path stored in map->arg, reads each line (up to count_line),
 * trims trailing newline characters, and stores each line in map->matrix.
 * Frees allocated memory and closes the file on error.
 *
 * @param map Pointer to the map structure, which contains the filename,
 *            line count, and will hold the matrix.
 * @return int 0 on success, -1 on failure (malloc or file errors).
 */
int	ft_fillmatrix(t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open (map->arg, O_RDONLY);
	map->matrix = malloc(sizeof(char *) * (map->count_line + 1));
	if (!map->matrix)
		return (close(fd), -1);
	while (i < map->count_line)
	{
		line = get_next_line(fd);
		map->matrix[i] = ft_strtrim(line, "\n");
		free(line);
		line = NULL;
		if (!map->matrix[i])
		{
			ft_free_matrix(map->matrix);
			return (close(fd), -1);
		}
		i++;
	}
	map->matrix[i] = NULL;
	return (close(fd), 0);
}

/**
 * @brief Wrapper function to fill the map matrix.
 *
 * Calls ft_fillmatrix if count_line is valid and returns the matrix.
 * Returns NULL if count_line is invalid.
 *
 * @param map Pointer to the map structure.
 * @return char** Pointer to the map matrix or NULL if error.
 */
char	**ft_fill_matrix(t_map *map)
{
	if (map->count_line < 0)
		return (NULL);
	ft_fillmatrix(map);
	return (map->matrix);
}

/**
 * @brief Checks the top and bottom borders of the map for walls ('1').
 *
 * Verifies that the first and last rows of the map are composed only of '1'.
 * Frees the matrix and returns error if any character differs.
 *
 * @param map Pointer to the map structure containing the matrix and dimensions.
 * @return int 0 if borders are valid, -1 otherwise.
 */
int	ft_check_x(t_map *map)
{
	int	i;

	i = 0;
	while (i < (map->line_len))
	{
		if ((map->matrix[0][i] != '1')
			|| (map->matrix[map->count_line - 1][i] != '1'))
		{
			ft_free_matrix(map->matrix);
			return (ft_printf(2, "Error\nErrore nei muri orizzontali"), -1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Checks the left and right borders of the map for walls ('1').
 *
 * Iterates through all rows except the first and last, verifying that the
 * first and last characters in each row are '1'. If any character on the
 * vertical borders differs, the function frees the map matrix, prints an error,
 * and returns -1.
 *
 * @param map Pointer to the map structure containing the matrix and dimensions.
 * @return int Returns 0 if all vertical borders are valid, -1 otherwise.
 */
int	ft_check_y(t_map *map)
{
	int	i;
	int	len;

	len = map->line_len;
	i = 1;
	while (i < ((map->count_line) - 1))
	{
		if ((map->matrix[i][0] != '1')
			|| (map->matrix[i][map->line_len - 1] != '1'))
		{
			ft_free_matrix(map->matrix);
			return (ft_printf(2, "Error\nErrore nei muri verticali"), -1);
		}
		i++;
	}
	return (0);
}
