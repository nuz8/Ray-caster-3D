/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 07:55:13 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 07:55:13 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool		init_column_bounds(t_game *game, t_column_ctx *ctx);
static bool		validate_target(t_game *game, t_column_ctx *ctx);
static bool		set_draw_limits(t_column_ctx *ctx, double start, double end);
static void		init_texture_sampling(t_column_ctx *ctx, double start);

void	render_column(t_game *game, t_column_ctx *ctx)
{
	int			y;
	int			tex_y;
	uint32_t	color;

	if (ctx->wall_height <= 0 || !ctx->texture)
		return ;
	if (!init_column_bounds(game, ctx))
		return ;
	y = ctx->draw_start;
	while (y <= ctx->draw_end)
	{
		tex_y = (int)ctx->tex_pos;
		color = column_sample_color(ctx, tex_y);
		column_write_texel(ctx, y, color);
		ctx->tex_pos += ctx->tex_step;
		y++;
	}
}

static bool	init_column_bounds(t_game *game, t_column_ctx *ctx)
{
	double	start;
	double	end;

	if (!validate_target(game, ctx))
		return (false);
	start = ((double)ctx->target->height - (double)ctx->wall_height) * 0.5;
	end = start + ctx->wall_height;
	if (!set_draw_limits(ctx, start, end))
		return (false);
	init_texture_sampling(ctx, start);
	return (ctx->dst != NULL);
}

static bool	validate_target(t_game *game, t_column_ctx *ctx)
{
	ctx->target = game->img_3d;
	if (!ctx->target || !ctx->target->pixels || !ctx->texture)
		return (false);
	ctx->width = ctx->target->width;
	if (ctx->screen_x < 0 || (uint32_t)ctx->screen_x >= ctx->width)
		return (false);
	return (ctx->wall_height > 0);
}

static bool	set_draw_limits(t_column_ctx *ctx, double start, double end)
{
	ctx->draw_start = (int)floor(start);
	ctx->draw_end = (int)ceil(end) - 1;
	if (ctx->draw_start < 0)
		ctx->draw_start = 0;
	if (ctx->draw_end >= (int)ctx->target->height)
		ctx->draw_end = (int)ctx->target->height - 1;
	if (ctx->draw_end < ctx->draw_start)
		return (false);
	return (true);
}

static void	init_texture_sampling(t_column_ctx *ctx, double start)
{
	ctx->tex_x = (int)(ctx->wall_u * ctx->texture->width);
	if (ctx->tex_x >= (int)ctx->texture->width)
		ctx->tex_x = ctx->texture->width - 1;
	if (ctx->tex_x < 0)
		ctx->tex_x = 0;
	ctx->tex_step = (double)ctx->texture->height / (double)ctx->wall_height;
	ctx->tex_pos = ((double)ctx->draw_start - start) * ctx->tex_step;
	ctx->dst = ctx->target->pixels;
}
