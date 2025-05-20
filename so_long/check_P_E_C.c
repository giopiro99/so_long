/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_P_E_C.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:16:59 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/06 12:23:05 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_ber(char *argv)
{
	if (ft_strncmp(argv + (ft_strlen(argv) - 4), ".ber", 4) == 0)
		return (0);
	else
		return (ft_printf("Error\nMappa non .ber"), -1);
}

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
		return (ft_printf("Error\nerrore negli elementi della mappa"), -1);
	}
	return (0);
}
