/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 07:23:24 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 07:23:31 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		init_events(void *param);

static void	upon_press(t_key keydata, void *param);
static void	upon_close(void *param);
static void	toggle_fov(t_game *game);

void	init_events(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_loop_hook(game->mlx, &game_loop, param);
	mlx_key_hook(game->mlx, &upon_press, param);
	mlx_close_hook(game->mlx, &upon_close, param);
}

static void	upon_press(t_key keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		upon_close(param);
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		toggle_fov(game);
}

static void	upon_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	exit_early(game, NULL, EXIT_SUCCESS);
}

static void	toggle_fov(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	t_rays		**rays;

	data = game->data;
	pl = game->player;
	rays = pl->rays;
	if (data->fov_toggle == true)
	{
		erase_previous_fov(pl, rays);
		data->fov_toggle = false;
	}
	else if (data->fov_toggle == false)
	{
		data->fov_toggle = true;
		draw_current_fov(pl, rays);
	}
	draw_cur_direction(pl, data);
}
