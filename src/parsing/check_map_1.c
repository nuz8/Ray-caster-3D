/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 05:25:26 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/05 20:58:34 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	player_counter_check(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	while (game->map->map_array[y])
	{
		x = 0;
		while (game->map->map_array[y][x])
		{
			if (game->map->map_array[y][x] == 'N'
				|| game->map->map_array[y][x] == 'E'
				|| game->map->map_array[y][x] == 'S'
				|| game->map->map_array[y][x] == 'W')
			{
				game->data->pl_arr_x = x;
				game->data->pl_arr_y = y;
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count);
}

static void	set_player_position_data(t_game *game)
{
	game->data->pl_posx = game->data->pl_arr_x * game->data->tile_size;
	game->data->pl_posy = game->data->pl_arr_y * game->data->tile_size;
	game->data->pl_center_x = game->data->pl_posx + game->data->tile_size / 2;
	game->data->pl_center_y = game->data->pl_posy + game->data->tile_size / 2;
	game->data->pl_posx_d = game->data->pl_posx;
	game->data->pl_posy_d = game->data->pl_posy;
	game->data->pl_center_x_d = game->data->pl_center_x;
	game->data->pl_center_y_d = game->data->pl_center_y;
}

static void	validate_map_walls(t_game *game)
{
	char	**dup_map;
	bool	valid;
	int		floodx;
	int		floody;

	dup_map = copy_map(game->map->map_array);
	if (!dup_map)
		exit_early(game, "Error: failed to duplicate map\n", 1);
	floodx = game->data->pl_posx / game->data->tile_size;
	floody = game->data->pl_posy / game->data->tile_size;
	valid = flood_fill(dup_map, floodx, floody);
	if (!valid)
		exit_early(game, "Error: map is not surrounded by walls\n", 1);
}

void	check_map(t_game *game)
{
	int	player_count;

	player_count = player_counter_check(game);
	if (player_count != 1)
		exit_early(game,
			"Error: map must contain exactly 1 player start position\n", 1);
	set_player_position_data(game);
	validate_map_walls(game);
}
