/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_02.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 07:45:20 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 07:45:20 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_distance(t_dvec *hype, t_ivec *check)
{
	if (hype[0].x < hype[0].y)
	{
		hype[2].x = hype[0].x;
		hype[0].x += hype[1].x;
		check->x = 1;
		check->y = 0;
	}
	else
	{
		hype[2].x = hype[0].y;
		hype[0].y += hype[1].y;
		check->x = 0;
		check->y = 1;
	}
}

void	extract_hit(t_rays *ray, t_ray_trace *ctx)
{
	double	hx;
	double	hy;

	hx = ctx->start.x + ctx->hype[2].x * ray->cosine;
	hy = ctx->start.y - ctx->hype[2].x * ray->sine;
	ctx->hit.x = (int)hx;
	ctx->hit.y = (int)hy;
	if (ctx->check.x)
	{
		if (ctx->hop.x < 0)
			ctx->hit.x--;
		else
			ctx->hit.x++;
	}
	else if (ctx->check.y)
	{
		if (ctx->hop.y < 0)
			ctx->hit.y--;
		else
			ctx->hit.y++;
	}
}

void	assign_wall_texture(t_game *game, t_rays *ray, t_dvec hop, t_ivec check)
{
	if (check.x == 1 && hop.x > 0)
	{
		ray->hit_wall = 'E';
		ray->tex = game->EA_texture;
	}
	else if (check.x == 1 && hop.x < 0)
	{
		ray->hit_wall = 'W';
		ray->tex = game->WE_texture;
	}
	else if (check.y == 1 && hop.y < 0)
	{
		ray->hit_wall = 'N';
		ray->tex = game->NO_texture;
	}
	else if (check.y == 1 && hop.y > 0)
	{
		ray->hit_wall = 'S';
		ray->tex = game->SO_texture;
	}
	else
		ray->hit_wall = 'X';
}
