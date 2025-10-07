/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:04:36 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 04:04:11 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		start_drawing(t_game *game);

static void	draw_minimap(t_game *game, char **map);

void	start_drawing(t_game *game)
{
	t_data		*data;
	t_player	*pl;
	char		**map;

	data = game->data;
	pl = game->player;
	map = game->map->map_array;
	cast_rays(pl->map, pl->rays, data);
	draw_3d_walls(game);
	draw_minimap(game, map);
	draw_current_fov(pl, pl->rays);
	place_player2D_2(game);
	draw_player_direction(game->player, data);
}

static void	draw_minimap(t_game *game, char **map)
{
	int	i;
	int	j;

	j = -1;
	while (map[++j])
	{
		i = -1;
		while (map[j][++i])
		{
			if (map[j][i] == '1')
				place_lined_block(game->map->image, i, j, STONE_GRAY);
			else if (map[j][i] == '0' || is_valid(map[j][i]))
				place_lined_block(game->map->image, i, j, DARK_GRAY);
		}
	}
}
