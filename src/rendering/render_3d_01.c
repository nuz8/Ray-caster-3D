/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 07:55:11 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 07:55:11 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_frame(t_game *game, t_wall_frame *frame);
static bool	prepare_column(t_game *game, t_wall_frame *frame,
				t_column_ctx *column);

void	draw_3d_walls(t_game *game)
{
	t_wall_frame	frame;
	t_column_ctx	column;

	if (!game || !game->img_3d)
		exit_early(game, "render_3d_walls: invalid target", EXIT_FAILURE);
	init_frame(game, &frame);
	while (frame.index < frame.total)
	{
		if (prepare_column(game, &frame, &column))
			render_column(game, &column);
		frame.index++;
	}
}

void	erase_3d_walls(t_game *game)
{
	size_t	pixel_count;
	t_img	*target;

	target = game->img_3d;
	if (!target || !target->pixels)
		return ;
	pixel_count = (size_t)target->width * (size_t)target->height;
	ft_bzero(target->pixels, pixel_count * sizeof(uint32_t));
}

static void	init_frame(t_game *game, t_wall_frame *frame)
{
	t_data	*data;

	data = game->data;
	frame->rays = game->player->rays;
	frame->total = data->num_rays;
	frame->index = 0;
	frame->scale = 15 * data->wind_h;
}

static bool	prepare_column(t_game *game, t_wall_frame *frame,
		t_column_ctx *column)
{
	t_rays	*ray;

	(void)game;
	ray = frame->rays[frame->index];
	if (!ray || ray->inv_wall_distance <= 0.0)
		return (false);
	frame->ray = ray;
	frame->height = (int)(frame->scale * ray->inv_wall_distance);
	frame->tex_u = ray->tex_u;
	if (frame->tex_u < 0.0f)
		frame->tex_u = 0.0f;
	else if (frame->tex_u > 1.0f)
		frame->tex_u = 1.0f;
	column->screen_x = frame->index;
	column->wall_height = frame->height;
	column->wall_u = frame->tex_u;
	column->texture = ray->tex;
	return (true);
}
