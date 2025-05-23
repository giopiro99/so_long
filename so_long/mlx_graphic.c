/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_graphic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:20:46 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/20 16:06:00 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Handles player movement based on the pressed key.
 *
 * If the key is W, A, S, or D, calls move_player with updated coordinates
 * corresponding to moving up, left, down, or right.
 *
 * @param map Pointer to the map structure containing state and positions.
 * @param keysym Keycode of the pressed key (XK_w, XK_a, XK_s, XK_d).
 */
void	ft_movevent(t_map *map, int keysym)
{
	if (keysym == XK_w || keysym == XK_a || keysym == XK_s || keysym == XK_d)
	{
		if (keysym == XK_w)
			move_player(map, map->y_p - 1, map->x_p, 0);
		else if (keysym == XK_s)
			move_player(map, map->y_p + 1, map->x_p, 1);
		else if (keysym == XK_a)
			move_player(map, map->y_p, map->x_p - 1, 2);
		else if (keysym == XK_d)
			move_player(map, map->y_p, map->x_p + 1, 3);
	}
}

/**
 * @brief Handles keyboard input and related actions.
 *
 * Calls ft_movevent for movement keys.
 * If the ESC key is pressed, closes the window, frees resources, and exits the program.
 *
 * @param keysym Keycode of the pressed key.
 * @param map Pointer to the map structure.
 * @return int Always returns 0.
 */
int	handle_input(int keysym, t_map *map)
{
	ft_movevent(map, keysym);
	if (keysym == XK_Escape)
	{
		close_window((void *)map);
		if (!map->mlx)
			return (0);
		free_image(map->mlx);
		ft_free_matrix(map->matrix);
		if (map->mlx->wp)
		{
			mlx_destroy_window(map->mlx->con, map->mlx->wp);
			map->mlx->wp = NULL;
		}
		if (map->mlx->con)
		{
			mlx_destroy_display(map->mlx->con);
			free(map->mlx->con);
			map->mlx->con = NULL;
		}
		free(map->mlx);
		exit (0);
	}
	return (0);
}

/**
 * @brief Creates and initializes the game window and graphical resources.
 *
 * Allocates the mlx structure, initializes the connection, creates the window,
 * loads images, draws the initial map, and sets event callbacks.
 * Starts the MLX main loop.
 *
 * @param map Pointer to the map structure.
 * @return int 0 on success, -1 on error.
 */
int	ft_create_window(t_map *map)
{
	map->mlx = malloc(sizeof(t_mlx));
	map->mlx->count_moves = 0;
	map->mlx->direction = 0;
	map->mlx->en_fram = 0;
	if (!map->mlx)
		return (-1);
	map->mlx->con = mlx_init();
	if (map->mlx->con == NULL)
		return (free(map->mlx), -1);
	map->mlx->wp = mlx_new_window(map->mlx->con, map->line_len * 48,
			map->count_line * 48, "So_Long");
	if (map->mlx->wp == NULL)
		return (mlx_destroy_display(map->mlx->con),
			free(map->mlx->con), free(map->mlx), -1);
	if (ft_create_image(map->mlx) == -1)
		return (ft_printf(2, "Error\nErrore nel caricamento delle i"), -1);
	ft_draw_background(map->mlx, map);
	ft_draw(map->mlx, map);
	mlx_hook(map->mlx->wp, 2, 1L << 0, handle_input, map);
	mlx_loop_hook(map->mlx->con, animate_enemy, (void *)map);
	mlx_hook(map->mlx->wp, 17, 0, close_window, map);
	mlx_loop(map->mlx->con);
	return (0);
}

/**
 * @brief Main setup function after parsing the map.
 *
 * Fills the matrix, checks horizontal and vertical walls, verifies map elements,
 * duplicates the matrix and uses flood fill to check reachability.
 * If all checks pass, creates the window and starts the game.
 *
 * @param map Pointer to the map structure.
 */
void	ft_for_main(t_map *map)
{
	map->matrix = ft_fill_matrix(map);
	if (map->count_line > 0 && map->line_len > 0)
	{
		if (ft_check_x(map) == 0)
		{
			if (ft_check_y(map) == 0)
			{
				if (ft_check_elements(map) == 0)
				{
					ft_duplicate_matrix(map);
					flood_fill(map, map->y_p, map->x_p, '1');
					if (ft_check_the_dup(map) == 0)
					{
						ft_free_matrix(map->dup_matrix);
						ft_create_window(map);
					}
					else
					{
						ft_free_matrix(map->matrix);
						ft_free_matrix(map->dup_matrix);
					}
				}
			}
		}
	}
}

/**
 * @brief Program entry point.
 *
 * Checks that the input file is passed and has a .ber extension,
 * runs parsing, and starts the game if the map is valid.
 *
 * @param argc Number of arguments passed.
 * @param argv Array of argument strings.
 * @return int Always returns 0.
 */
int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc == 2)
	{
		if (ft_check_ber(argv[1]) == 0)
		{
			map.arg = argv[1];
			if (ft_parsing(&map) > 0)
					ft_for_main(&map);
		}
	}
	return (0);
}
