/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:35:13 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:35:13 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	rotation_step(t_game *game)
{
	double	step;

	step = PI / 180;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		step *= 4;
	return (step);
}

bool	turn_player(t_game *game)
{
	t_data	*data;
	double	step;
	double	delta;

	data = game->data;
	step = rotation_step(game);
	delta = 0.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_Q))
		delta += step;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_E))
		delta -= step;
	if (delta == 0.0)
		return (false);
	data->prev_dir = data->cur_dir;
	data->cur_dir += delta;
	if (data->cur_dir < 0)
		data->cur_dir += 2 * PI;
	else if (data->cur_dir >= 2 * PI)
		data->cur_dir -= 2 * PI;
	return (true);
}

void	clear_player_view(t_game *game)
{
	t_player	*pl;
	t_data		*data;

	pl = game->player;
	data = game->data;
	erase_prev_direction(pl, data);
	erase_previous_fov(pl, pl->rays);
	erase_3d_walls(game);
}

void	print_fps(t_data *data)
{
	double	time_current;
	double	time_delta;

	data->fps++;
	time_current = mlx_get_time();
	time_delta = time_current - data->time;
	data->acc_time += time_delta;
	data->time = time_current;
	if (data->acc_time < 1.0)
		return ;
	printf("FPS: %d\n", data->fps);
	data->acc_time = 0;
	data->fps = 0;
}
