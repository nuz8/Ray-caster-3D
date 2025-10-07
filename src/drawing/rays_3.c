/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 06:28:31 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 06:44:21 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	init_direction_ctx(t_player *pl, t_data *data, double angle,
		t_dir_ctx *ctx)
{
	t_img	*view;

	view = pl->view;
	if (!view)
		return (false);
	ctx->center_x = data->pl_center_x_d;
	ctx->center_y = data->pl_center_y_d;
	ctx->scale = data->mmp_scale;
	ctx->width = (int)view->width;
	ctx->height = (int)view->height;
	if (ctx->width <= 0 || ctx->height <= 0)
		return (false);
	ctx->cosine = cos(angle);
	ctx->sine = sin(angle);
	return (true);
}

void	draw_direction_line(t_player *pl, t_dir_ctx *ctx, uint32_t colour)
{
	int	step;
	int	ix;
	int	iy;

	step = 0;
	while (step++ < PL_DIR_LEN)
	{
		ix = world_to_minimap(ctx->center_x + step * ctx->cosine, ctx->scale);
		iy = world_to_minimap(ctx->center_y - step * ctx->sine, ctx->scale);
		if (ix < 0 || ix >= ctx->width || iy < 0 || iy >= ctx->height)
			continue ;
		mlx_put_pixel(pl->view, ix, iy, colour);
	}
}

int	world_to_minimap(double value, double scale)
{
	return ((int)lround(value * scale));
}

bool	init_ray_ctx(t_player *pl, t_rays *ray, t_ray_ctx *ctx)
{
	t_img	*view;
	t_data	*data;

	if (!pl || !ray)
		return (false);
	view = pl->view;
	data = pl->data;
	if (!view || !data || ray->length <= 0.0)
		return (false);
	ctx->width = (int)view->width;
	ctx->height = (int)view->height;
	if (ctx->width <= 0 || ctx->height <= 0)
		return (false);
	ctx->scale = data->mmp_scale;
	ctx->start_x = *ray->center_x_d;
	ctx->start_y = *ray->center_y_d;
	ctx->cosine = ray->cosine;
	ctx->sine = ray->sine;
	ctx->steps = ft_maxi(1, (int)ceil(ray->length));
	ctx->prev_ix = 0;
	ctx->prev_iy = 0;
	ctx->first = true;
	return (true);
}

void	plot_ray_pixels(t_player *pl, t_ray_ctx *ctx, uint32_t colour)
{
	int	i;
	int	ix;
	int	iy;

	i = -1;
	while (++i <= ctx->steps)
	{
		ix = world_to_minimap(ctx->start_x + i * ctx->cosine, ctx->scale);
		iy = world_to_minimap(ctx->start_y - i * ctx->sine, ctx->scale);
		if (!ctx->first && ix == ctx->prev_ix && iy == ctx->prev_iy)
			continue ;
		ctx->first = false;
		ctx->prev_ix = ix;
		ctx->prev_iy = iy;
		if (ix < 0 || ix >= ctx->width || iy < 0 || iy >= ctx->height)
			continue ;
		mlx_put_pixel(pl->view, ix, iy, colour);
	}
}
