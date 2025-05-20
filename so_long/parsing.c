/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:41 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:00:13 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Counts the number of non-empty lines in the map file.
 *
 * Opens the file indicated by map->arg and reads it line by line,
 * counting only lines that are not empty or just newline.
 * Limits the maximum line count to 20; returns -1 if exceeded.
 *
 * @param map Pointer to the map structure containing the filename.
 * @return int Number of valid lines or -1 if too many lines.
 */
int	ft_count_line(t_map *map)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(map->arg, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '\0')
			i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (i > 20)
		return (-1);
	return (i);
}

/**
 * @brief Checks if the given line is empty or null.
 *
 * Frees the line if it is empty or null, returns 1 to indicate error.
 * Otherwise returns 0.
 *
 * @param line Pointer to the line pointer to check.
 * @return int 1 if line is invalid, 0 otherwise.
 */
static int	ft_check(char **line)
{
	if (!*line || *line[0] == '\n' || *line[0] == '\0')
	{
		free(*line);
		return (1);
	}
	return (0);
}

/**
 * @brief Checks that all lines have the same length and length constraints.
 *
 * Reads `count_line` lines from the map file and trims newline characters.
 * Verifies each line length matches the first line length and that
 * no line exceeds length 41. Returns the line length or -1 if invalid.
 *
 * @param len_line1 Length of the first line.
 * @param count_line Number of lines to check.
 * @param map Pointer to the map structure containing the filename.
 * @return int Length of the lines if valid, otherwise -1.
 */
int	ft_check_len_line(int len_line1, int count_line, t_map *map)
{
	char	*line;
	char	*trim_line;
	int		len_line;
	int		i;
	int		fd;

	i = 0;
	fd = open(map->arg, O_RDONLY);
	while (i++ < count_line)
	{
		line = get_next_line(fd);
		if (ft_check(&line) == 1)
			break ;
		trim_line = ft_strtrim(line, "\n");
		len_line = (int)ft_strlen(trim_line);
		if (len_line1 != len_line || len_line > 41)
		{
			close(fd);
			return (free(line), free(trim_line), -1);
		}
		free(trim_line);
		free(line);
	}
	return (close(fd), len_line);
}

/**
 * @brief Parses the map file, verifying its format and size.
 *
 * Opens the map file and validates its existence and basic structure.
 * Calls helper functions to count lines and verify line lengths.
 * Prints error messages on failure or confirms rectangularity on success.
 *
 * @param map Pointer to the map structure containing the filename.
 * @return int Number of lines if successful, -1 on failure.
 */
int	ft_parsing(t_map *map)
{
	char	*line;
	char	*trim_line;
	int		len_line1;
	int		fd;

	len_line1 = 0;
	fd = open(map->arg, O_RDWR);
	if (fd < 0)
		return (ft_printf(2, "Error\nErrore, impossibile aprire il file"), -1);
	line = get_next_line(fd);
	if (!line || line[0] == '\n' || line[0] == '\0')
		return (close(fd), free(line), ft_printf(2, "Error\nmappa non esiste"), -1);
	trim_line = ft_strtrim(line, "\n");
	len_line1 = (int)ft_strlen(trim_line);
	free(line);
	free(trim_line);
	close(fd);
	map->count_line = ft_count_line(map);
	if (map->count_line == -1)
		return (ft_printf(2, "Error\nErrore mappa troppo grande"), -1);
	map->line_len = ft_check_len_line(len_line1, map->count_line, map);
	if (map->line_len == -1)
		return (ft_printf(2, "Error\nError len line"), -1);
	return (ft_printf(1, "La mappa e' rettangolare\n"), map->count_line);
}

/*
int main()
{
	t_map	map;
	ft_parsing(&map);
}
 */
