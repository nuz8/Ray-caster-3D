/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:48:37 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 03:47:09 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <stddef.h>

static t_offsets_info	circle_offsets(void)
{
	static const t_vec2	offsets[] = {{0.0, 0.0}, {1.0, 0.0}, {-1.0, 0.0},
	{0.0, 1.0}, {0.0, -1.0}, {1.0, 1.0}, {1.0, -1.0}, {-1.0, 1.0}, {-1.0, -1.0},
	{1.0, 0.5}, {1.0, -0.5}, {-1.0, 0.5}, {-1.0, -0.5}, {0.5, 1.0},
	{-0.5, 1.0}, {0.5, -1.0}, {-0.5, -1.0}};
	t_offsets_info		info;

	info.arr = offsets;
	info.count = sizeof(offsets) / sizeof(offsets[0]);
	return (info);
}

static bool	sample_circle(const t_circle_ctx *ctx, double center_x,
		double center_y)
{
	t_offsets_info	info;
	size_t			idx;
	int				px;
	int				py;

	info = circle_offsets();
	if (center_x - ctx->radius < 0.0 || center_y - ctx->radius < 0.0
		|| center_x + ctx->radius >= (double)ctx->width || center_y
		+ ctx->radius >= (double)ctx->height)
		return (true);
	idx = 0;
	while (idx < info.count)
	{
		px = (int)floor(center_x + info.arr[idx].x * ctx->radius);
		py = (int)floor(center_y + info.arr[idx].y * ctx->radius);
		if (px < 0 || px >= ctx->width || py < 0 || py >= ctx->height)
			return (true);
		if (ctx->img[py][px] == '1')
			return (true);
		idx++;
	}
	return (false);
}

bool	wall_collision_circle(t_map *map, double center_x, double center_y)
{
	t_circle_ctx	ctx;

	if (!map || !map->data || !map->img_array)
		return (true);
	ctx.data = map->data;
	ctx.img = map->img_array;
	ctx.radius = (double)ctx.data->pl_dia * 0.5;
	ctx.width = ctx.data->mmp_w;
	ctx.height = ctx.data->mmp_h;
	if (ctx.radius <= 0.0)
		return (false);
	return (sample_circle(&ctx, center_x, center_y));
}
