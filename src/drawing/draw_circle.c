/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:44:04 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 06:20:09 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int		clamped_radius(t_data *data, int center_x, int center_y);
static void		draw_filled_circle_smooth(t_img *img, int center_x,
					int center_y, int radius);
static float	circle_distance(int x, int y, int center_x, int center_y);
static uint32_t	blend_color(uint32_t color, float alpha);

void	place_player_2d(t_game *game)
{
	t_img	*img;
	int		center_x;
	int		center_y;
	int		radius;

	img = game->player->blob_2d;
	if (!img || img->width == 0 || img->height == 0)
		return ;
	center_x = (int)(img->width / 2);
	center_y = (int)(img->height / 2);
	radius = clamped_radius(game->data, center_x, center_y);
	if (radius <= 0)
	{
		mlx_put_pixel(img, center_x, center_y, RED);
		return ;
	}
	draw_filled_circle_smooth(img, center_x, center_y, radius);
}

static int	clamped_radius(t_data *data, int center_x, int center_y)
{
	int	radius;

	if (data->pl_dia_mm <= 0)
		return (0);
	radius = data->pl_dia_mm / 2;
	if (radius < 1)
		radius = 1;
	if (radius > center_x)
		radius = center_x;
	if (radius > center_y)
		radius = center_y;
	return (radius);
}

static void	draw_filled_circle_smooth(t_img *img, int center_x, int center_y,
		int radius)
{
	int		x;
	int		y;
	float	distance;

	y = center_y - radius - 1;
	while (++y <= center_y + radius + 1)
	{
		x = center_x - radius - 1;
		while (++x <= center_x + radius + 1)
		{
			if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
				continue ;
			distance = circle_distance(x, y, center_x, center_y);
			if (distance > radius + 0.5f)
				continue ;
			if (distance > radius - 0.5f)
				mlx_put_pixel(img, x, y, blend_color(RED, radius + 0.5f
						- distance));
			else
				mlx_put_pixel(img, x, y, RED);
		}
	}
}

static float	circle_distance(int x, int y, int center_x, int center_y)
{
	float	dx;
	float	dy;

	dx = (float)(x - center_x);
	dy = (float)(y - center_y);
	return (sqrtf(dx * dx + dy * dy));
}

static uint32_t	blend_color(uint32_t color, float alpha)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	alpha_channel;

	if (alpha >= 1.0f)
		return (color);
	if (alpha <= 0.0f)
		return (0x00000000);
	r = (uint8_t)((color >> 24) & 0xFF);
	g = (uint8_t)((color >> 16) & 0xFF);
	b = (uint8_t)((color >> 8) & 0xFF);
	alpha_channel = (uint8_t)(color & 0xFF);
	alpha_channel = (uint8_t)(alpha_channel * alpha);
	return ((r << 24) | (g << 16) | (b << 8) | alpha_channel);
}
