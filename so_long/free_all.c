/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:24:33 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/02/05 12:32:35 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_image(t_mlx *mlx)
{
	if (mlx->sf)
		mlx_destroy_image(mlx->con, mlx->sf);
	if (mlx->muro)
		mlx_destroy_image(mlx->con, mlx->muro);
	if (mlx->play)
		mlx_destroy_image(mlx->con, mlx->play);
	if (mlx->coll)
		mlx_destroy_image(mlx->con, mlx->coll);
	if (mlx->exit)
		mlx_destroy_image(mlx->con, mlx->exit);
	if (mlx->enemy)
		mlx_destroy_image(mlx->con, mlx->enemy);
	if (mlx->en_mov)
		mlx_destroy_image(mlx->con, mlx->en_mov);
	if (mlx->p_up)
		mlx_destroy_image(mlx->con, mlx->p_up);
	if (mlx->p_sx)
		mlx_destroy_image(mlx->con, mlx->p_sx);
}

int	close_window(void *map)
{
	t_map	*mapp;

	mapp = (t_map *)map;
	if (mapp->mlx == NULL)
		return (0);
	free_image(mapp->mlx);
	ft_free_matrix(mapp->matrix);
	if (mapp->mlx->wp)
	{
		mlx_destroy_window(mapp->mlx->con, mapp->mlx->wp);
		mapp->mlx->wp = NULL;
	}
	if (mapp->mlx->con)
	{
		mlx_destroy_display(mapp->mlx->con);
		free(mapp->mlx->con);
		mapp->mlx->con = NULL;
	}
	free(mapp->mlx);
	exit (0);
	return (0);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (matrix)
	{
		while (matrix[i] != NULL)
		{
			free(matrix[i]);
			matrix[i] = NULL;
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
}
