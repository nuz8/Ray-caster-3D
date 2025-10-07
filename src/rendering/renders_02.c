/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:05:13 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:05:13 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_minimap_view(t_game *game, t_map *map)
{
	t_data	*data;

	data = game->data;
	if (map->image_inst_id != -1)
		return ;
	map->image_inst_id = mlx_image_to_window(game->mlx, map->image,
			data->mmp_offx, data->mmp_offy);
	if (map->image_inst_id < 0)
		exit_early(game, "map_image: mlx_image_to_window", EXIT_FAILURE);
}

void	render_player_blob(t_game *game, t_player *pl)
{
	t_data		*data;
	t_blob_ctx	ctx;

	data = game->data;
	if (!pl->blob_2d)
		return ;
	ctx.scale = data->mmp_scale;
	ctx.width = (int)pl->blob_2d->width;
	ctx.height = (int)pl->blob_2d->height;
	ctx.draw_x = (int)lround(data->pl_center_x_d * ctx.scale) - ctx.width / 2
		+ data->mmp_offx;
	ctx.draw_y = (int)lround(data->pl_center_y_d * ctx.scale) - ctx.height / 2
		+ data->mmp_offy;
	if (pl->blob_inst_id == -1)
	{
		pl->blob_inst_id = mlx_image_to_window(game->mlx, pl->blob_2d,
				ctx.draw_x, ctx.draw_y);
		if (pl->blob_inst_id < 0)
			exit_early(game, "blob2d: mlx_image_to_window", EXIT_FAILURE);
		return ;
	}
	pl->blob_2d->instances[pl->blob_inst_id].x = ctx.draw_x;
	pl->blob_2d->instances[pl->blob_inst_id].y = ctx.draw_y;
}

void	render_2d_view(t_game *game, t_player *pl)
{
	t_data	*data;

	data = game->data;
	if (pl->view_inst_id == -1)
	{
		pl->view_inst_id = mlx_image_to_window(game->mlx, pl->view,
				data->mmp_offx, data->mmp_offy);
		if (pl->view_inst_id < 0)
			exit_early(game, "2d_view: mlx_image_to_window", EXIT_FAILURE);
		return ;
	}
	pl->view->instances[pl->view_inst_id].x = data->mmp_offx
		+ data->debug_offset_x;
	pl->view->instances[pl->view_inst_id].y = data->mmp_offy
		+ data->debug_offset_y;
}
