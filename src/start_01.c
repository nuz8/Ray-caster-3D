/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:35:11 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:35:11 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		handle_player_movements(t_game *game);
static bool		turn_input_active(t_game *game);
static bool		move_input_active(t_game *game);
static void		refresh_direction_view(t_game *game);

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_player_movements(game);
	render_graphics(game);
	print_fps(game->data);
}

static void	handle_player_movements(t_game *game)
{
	bool	turned;
	bool	moved;
	bool	view_cleared;

	view_cleared = false;
	turned = false;
	if (turn_input_active(game) && turn_player(game))
	{
		clear_player_view(game);
		view_cleared = true;
		turned = true;
	}
	moved = false;
	if (move_input_active(game))
	{
		if (!view_cleared)
		{
			clear_player_view(game);
			view_cleared = true;
		}
		moved = move_player(game);
	}
	if (turned || moved || view_cleared)
		refresh_direction_view(game);
}

static bool	turn_input_active(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		return (true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_Q))
		return (true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		return (true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		return (true);
	return (false);
}

static bool	move_input_active(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		return (true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		return (true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		return (true);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		return (true);
	return (false);
}

static void	refresh_direction_view(t_game *game)
{
	t_player	*pl;
	t_data		*data;

	pl = game->player;
	data = game->data;
	udpate_rays(pl->rays, game->map, data);
	draw_3d_walls(game);
	draw_current_fov(pl, pl->rays);
	draw_cur_direction(pl, data);
	data->prev_dir = data->cur_dir;
}
