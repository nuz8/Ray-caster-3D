/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders_01.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:05:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:05:12 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	render_background(t_game *game);
static void	render_3d_view(t_game *game);

void	render_graphics(t_game *game)
{
	t_map		*map;
	t_player	*pl;

	map = game->map;
	pl = game->player;
	render_background(game);
	render_3d_view(game);
	render_minimap_view(game, map);
	render_2d_view(game, pl);
	render_player_blob(game, pl);
}

static void	render_background(t_game *game)
{
	if (game->background_inst_id != -1)
		return ;
	game->background_inst_id = mlx_image_to_window(game->mlx,
			game->background, 0, 0);
	if (game->background_inst_id < 0)
		exit_early(game, "background_image: mlx_image_to_window", EXIT_FAILURE);
}

static void	render_3d_view(t_game *game)
{
	if (game->img_3d_inst_id != -1)
		return ;
	game->img_3d_inst_id = mlx_image_to_window(game->mlx, game->img_3d, 0, 0);
	if (game->img_3d_inst_id < 0)
		exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
}
