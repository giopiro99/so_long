/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:07 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/05 12:33:01 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

char	**ft_fill_matrix(t_map *map)
{
	if (map->count_line < 0)
		return (NULL);
	ft_fillmatrix(map);
	return (map->matrix);
}

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
			return (ft_printf("Error\nErrore nei muri orizzontali", -1));
		}
		i++;
	}
	return (0);
}

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
			return (ft_printf("Error\nErrore nei muri verticali", -1));
		}
		i++;
	}
	return (0);
}
