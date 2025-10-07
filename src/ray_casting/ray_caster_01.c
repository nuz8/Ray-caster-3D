/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 07:45:18 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 07:45:18 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	trace_single_ray(t_game *game, t_rays *ray, char **img,
				t_data *data);
static void	init_trace_context(t_ray_trace *ctx, t_rays *ray, t_data *data);
static bool	is_wall_hit(char **img, t_data *data, t_ray_trace *ctx);
static void	handle_wall_hit(t_game *game, t_rays *ray, t_ray_trace *ctx);

void	cast_rays(t_map *map, t_rays **rays, t_data *data)
{
	t_game	*game;
	char	**img;
	int		total;
	int		i;

	game = map->game;
	img = map->img_array;
	total = data->num_rays;
	i = -1;
	while (++i < total)
		trace_single_ray(game, rays[i], img, data);
}

static void	trace_single_ray(t_game *game, t_rays *ray, char **img,
		t_data *data)
{
	t_ray_trace	ctx;

	init_trace_context(&ctx, ray, data);
	while (ctx.hype[2].x <= ctx.hype[2].y)
	{
		update_distance(ctx.hype, &ctx.check);
		extract_hit(ray, &ctx);
		if (!is_wall_hit(img, data, &ctx))
			continue ;
		handle_wall_hit(game, ray, &ctx);
		return ;
	}
}

static void	init_trace_context(t_ray_trace *ctx, t_rays *ray, t_data *data)
{
	ctx->start.x = *ray->center_x_d;
	ctx->start.y = *ray->center_y_d;
	ctx->inv_tile = data->inv_tile_size;
	if (ctx->inv_tile <= 0.0 && data->tile_size > 0)
		ctx->inv_tile = 1.0 / (double)data->tile_size;
	ray->inv_wall_distance = 0.0;
	ray->tex_u = 0.0;
	initialize_ray_caster(ray, data, (t_dvec *[]){&ctx->hop, ctx->hype},
		&ctx->check);
}

static bool	is_wall_hit(char **img, t_data *data, t_ray_trace *ctx)
{
	int	x;
	int	y;

	x = ctx->hit.x;
	y = ctx->hit.y;
	if (x < 0 || x >= data->mmp_w)
		return (false);
	if (y < 0 || y >= data->mmp_h)
		return (false);
	return (img[y][x] == '1');
}

static void	handle_wall_hit(t_game *game, t_rays *ray, t_ray_trace *ctx)
{
	double	distance;
	double	tile_pos;

	distance = ctx->hype[2].x;
	ray->length = distance;
	ray->wall_distance = distance * cos(ray->delta);
	if (ray->wall_distance > 1e-6)
		ray->inv_wall_distance = 1.0 / ray->wall_distance;
	else
		ray->inv_wall_distance = 0.0;
	ray->hit_x = ctx->start.x + distance * ray->cosine;
	ray->hit_y = ctx->start.y - distance * ray->sine;
	assign_wall_texture(game, ray, ctx->hop, ctx->check);
	if (ray->hit_wall == 'N' || ray->hit_wall == 'S')
		tile_pos = ray->hit_x * ctx->inv_tile;
	else
		tile_pos = ray->hit_y * ctx->inv_tile;
	ray->tex_u = tile_pos - floor(tile_pos);
	if (ray->tex_u < 0.0)
		ray->tex_u += 1.0;
}
