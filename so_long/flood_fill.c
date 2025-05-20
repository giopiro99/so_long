/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:17:15 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/05 12:33:10 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_dup_matrix(t_map *map)
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
				return (ft_printf("Error\nE non e' raggiungibile"), -1);
			if (map->dup_matrix[i][j] == 'C')
				return (ft_printf("Error\nC non raggiungibili"), -1);
			j++;
		}
		j = 0;
		i ++;
	}
	return (0);
}
