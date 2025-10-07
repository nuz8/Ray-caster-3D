/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:44:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 06:14:30 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	minimap_tile_bounds(t_img *img, int tile_x, int tile_y,
				t_rect *rect);
static void	draw_solid_block(t_img *img, t_rect rect, int block_color);
static void	draw_lined_block(t_img *img, t_rect rect, int block_color);

static bool	minimap_tile_bounds(t_img *img, int tile_x, int tile_y,
		t_rect *rect)
{
	double	step;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;

	step = tile_step();
	init_tile_edges(step, tile_x, &start_x, &end_x);
	init_tile_edges(step, tile_y, &start_y, &end_y);
	if (!validate_edge(&start_x, &end_x, (int)img->width)
		|| !validate_edge(&start_y, &end_y, (int)img->height))
		return (false);
	rect->x0 = start_x;
	rect->y0 = start_y;
	rect->x1 = end_x;
	rect->y1 = end_y;
	return (true);
}

static void	draw_solid_block(t_img *img, t_rect rect, int block_color)
{
	int	width;
	int	height;
	int	i;
	int	j;

	width = rect.x1 - rect.x0;
	height = rect.y1 - rect.y0;
	if (width <= 0 || height <= 0)
		return ;
	if (width <= 1 || height <= 1)
	{
		mlx_put_pixel(img, rect.x0, rect.y0, block_color);
		return ;
	}
	j = -1;
	while (++j < height - 1)
	{
		i = -1;
		while (++i < width - 1)
			mlx_put_pixel(img, rect.x0 + i, rect.y0 + j, block_color);
	}
}

static void	draw_lined_block(t_img *img, t_rect rect, int block_color)
{
	int	width;
	int	height;
	int	i;
	int	j;

	width = rect.x1 - rect.x0;
	height = rect.y1 - rect.y0;
	if (width <= 0 || height <= 0)
		return ;
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			if (is_border_pixel(i, j, width, height))
				mlx_put_pixel(img, rect.x0 + i, rect.y0 + j, BLACK);
			else if (block_color != 0)
				mlx_put_pixel(img, rect.x0 + i, rect.y0 + j,
					(uint32_t)block_color);
		}
	}
}

void	place_block(t_img *img, int x, int y, int block_color)
{
	t_rect	rect;

	if (!block_color)
		return ;
	if (!minimap_tile_bounds(img, x, y, &rect))
		return ;
	draw_solid_block(img, rect, block_color);
}

void	place_lined_block(t_img *img, int x, int y, int block_color)
{
	t_rect	rect;

	if (!minimap_tile_bounds(img, x, y, &rect))
		return ;
	draw_lined_block(img, rect, block_color);
}
