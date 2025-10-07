/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:35:12 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:35:12 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

typedef struct s_move_ctx
{
	t_data	*data;
	t_map	*map;
	double	base_x;
	double	base_y;
	double	final_x;
	double	final_y;
	double	move_x;
	double	move_y;
	double	step;
	int		step_half;
	bool	moved;
}		t_move_ctx;

static void	add_move_component(t_move_ctx *ctx, double x, double y);
static void	setup_move_ctx(t_game *game, t_move_ctx *ctx);
static bool	resolve_movement(t_move_ctx *ctx);
static void	try_move_axis(t_move_ctx *ctx, double candidate, bool horizontal);

bool	move_player(t_game *game)
{
	t_move_ctx	ctx;
	t_data		*data;

	setup_move_ctx(game, &ctx);
	if (!resolve_movement(&ctx) || !ctx.moved)
		return (false);
	data = ctx.data;
	if (ctx.final_x != ctx.base_x)
	{
		data->pl_posx_d = ctx.final_x;
		data->pl_center_x_d = ctx.final_x + ctx.step_half;
		data->pl_posx = (int)lround(ctx.final_x);
		data->pl_center_x = data->pl_posx + ctx.step_half;
	}
	if (ctx.final_y != ctx.base_y)
	{
		data->pl_posy_d = ctx.final_y;
		data->pl_center_y_d = ctx.final_y + ctx.step_half;
		data->pl_posy = (int)lround(ctx.final_y);
		data->pl_center_y = data->pl_posy + ctx.step_half;
	}
	return (true);
}

static void	add_move_component(t_move_ctx *ctx, double x, double y)
{
	ctx->move_x += x * ctx->step;
	ctx->move_y += y * ctx->step;
}

static void	setup_move_ctx(t_game *game, t_move_ctx *ctx)
{
	t_data	*data;

	data = game->data;
	ctx->data = data;
	ctx->map = game->map;
	ctx->base_x = data->pl_posx_d;
	ctx->base_y = data->pl_posy_d;
	ctx->final_x = ctx->base_x;
	ctx->final_y = ctx->base_y;
	ctx->move_x = 0.0;
	ctx->move_y = 0.0;
	ctx->step = 1.0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		ctx->step *= 5.0;
	ctx->step_half = data->tile_size / 2;
	ctx->moved = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		add_move_component(ctx, data->cosine, -data->sine);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		add_move_component(ctx, -data->cosine, data->sine);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		add_move_component(ctx, -data->sine, -data->cosine);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		add_move_component(ctx, data->sine, data->cosine);
}

static bool	resolve_movement(t_move_ctx *ctx)
{
	if (!ctx->map || !ctx->map->img_array)
		return (false);
	if (ctx->move_x == 0.0 && ctx->move_y == 0.0)
		return (false);
	if (ctx->move_x != 0.0)
		try_move_axis(ctx, ctx->base_x + ctx->move_x, true);
	if (ctx->move_y != 0.0)
		try_move_axis(ctx, ctx->base_y + ctx->move_y, false);
	return (true);
}

static void	try_move_axis(t_move_ctx *ctx, double candidate, bool horizontal)
{
	double	center_x;
	double	center_y;

	if (horizontal)
	{
		center_x = candidate + ctx->step_half;
		center_y = ctx->base_y + ctx->step_half;
		if (wall_collision_circle(ctx->map, center_x, center_y))
			return ;
		ctx->final_x = candidate;
		ctx->moved = true;
		return ;
	}
	center_x = ctx->final_x + ctx->step_half;
	center_y = candidate + ctx->step_half;
	if (wall_collision_circle(ctx->map, center_x, center_y))
		return ;
	ctx->final_y = candidate;
	ctx->moved = true;
}
