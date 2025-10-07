/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 16:44:04 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 04:00:57 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include <math.h>

void			place_player2D_2(t_game *game);

static void		draw_filled_circle_smooth(t_img *img, int center_x,
					int center_y, int radius, uint32_t color);
static uint32_t	blend_color(uint32_t color, float alpha);

void	place_player2D_2(t_game *game)
{
	t_img	*img;
	t_data	*data;
	int		center_x;
	int		center_y;
	int		radius;

	img = game->player->blob2D;
	data = game->data;
	if (!img || img->width == 0 || img->height == 0)
		return ;
	center_x = (int)(img->width / 2);
	center_y = (int)(img->height / 2);
	radius = data->pl_dia_mm / 2;
	if (radius < 1 && data->pl_dia_mm > 0)
		radius = 1;
	if (radius > center_x)
		radius = center_x;
	if (radius > center_y)
		radius = center_y;
	if (radius <= 0)
	{
		mlx_put_pixel(img, center_x, center_y, RED);
		return ;
	}
	draw_filled_circle_smooth(img, center_x, center_y, radius, RED);
}

static void	draw_filled_circle_smooth(t_img *img, int center_x, int center_y,
		int radius, uint32_t color)
{
	float		radius_f;
	int			radius_ceil;
	int			x;
	int			y;
	float		dx;
	float		dy;
	float		distance;
	float		alpha;
	uint32_t	blended_color;

	radius_f = (float)radius;
	radius_ceil = radius + 1;
	y = center_y - radius;
	while (++y <= center_y + radius_ceil)
	{
		x = center_x - radius;
		while (++x <= center_x + radius_ceil)
		{
			if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
			{
				dx = (float)(x - center_x);
				dy = (float)(y - center_y);
				distance = sqrtf(dx * dx + dy * dy);
				if (distance <= radius_f + 0.5f)
				{
					if (distance > radius_f - 0.5f)
					{
						alpha = (radius_f + 0.5f - distance);
						blended_color = blend_color(color, alpha);
						mlx_put_pixel(img, x, y, blended_color);
					}
					else
						mlx_put_pixel(img, x, y, color);
				}
			}
		}
	}
}

static uint32_t	blend_color(uint32_t color, float alpha)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	original_alpha;
	uint8_t	new_alpha;

	if (alpha >= 1.0f)
		return (color);
	if (alpha <= 0.0f)
		return (0x00000000);
	r = (uint8_t)((color >> 24) & 0xFF);
	g = (uint8_t)((color >> 16) & 0xFF);
	b = (uint8_t)((color >> 8) & 0xFF);
	original_alpha = (uint8_t)(color & 0xFF);
	new_alpha = (uint8_t)(original_alpha * alpha);
	return ((r << 24) | (g << 16) | (b << 8) | new_alpha);
}
