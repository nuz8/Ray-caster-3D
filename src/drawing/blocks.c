/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 16:44:50 by pamatya           #+#    #+#             */
/*   Updated: 2025/08/24 17:05:03 by pamatya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

typedef struct s_rect
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_rect;

static bool	minimap_tile_bounds(t_img *img, int tile_x, int tile_y, t_rect *rect);

void	place_block(t_img *img, int i, int j, int block_color);
void	place_block2(t_img *img, int i, int j, int block_color, int bls);
void	place_lined_block(t_img *img, int x, int y, int block_color);

/*
Function to place a block/tile of size as defined in the HEADER as TILE_SIZE
  - if block color is provided as 0, then block_color will be white
  - x and y are the starting coordinates (from upper left corner) of blocks in a
  	tiled world representing the whole block of several pixels TILE_SIZE in 
	width and height
  - the final row and column of the block is not drawn to provide a checkered
    pattern
*/
void	place_block(t_img *img, int x, int y, int block_color)
{
	t_rect	rect;
	int		width;
	int		height;
	int		i;
	int		j;

	if (!block_color)
		return ;
	if (!minimap_tile_bounds(img, x, y, &rect))
		return ;
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

// /*
// Function to place a block/tile of size as defined in the HEADER as TILE_SIZE
//   - if block color is provided as 0, then block_color will be white
//   - x and y are the starting coordinates (from upper left corner) of blocks in a
//   	tiled world representing the whole block of several pixels TILE_SIZE in 
// 	width and height
// */
// void	place_block(t_img *img, int x, int y, int block_color)
// {
// 	int		i;
// 	int		j;
// 	t_data	*data;

// 	if (!block_color)
// 		return ;
// 	data = get_data();
// 	j = -1;
// 	while (++j < data->tile_size)
// 	{
// 		i = -1;
// 		while (++i < data->tile_size)
// 		{
// 			mlx_put_pixel(img, x * data->tile_size + i,
// 					y * data->tile_size + j, block_color);
// 		}
// 	}
// }

// bls = TILE_SIZE 
void	place_block2(t_img *img, int x, int y, int block_color, int bls)
{
	int		i;
	int		j;

	if (!block_color)
		return ;
	j = -1;
	while (++j < bls)
	{
		i = -1;
		while (++i < bls)
			mlx_put_pixel(img, x * bls + i, y * bls + j,
					block_color);
	}
}

void	place_lined_block(t_img *img, int x, int y, int block_color)
{
	t_rect	rect;
	int		width;
	int		height;
	int		i;
	int		j;
	uint32_t	border;

	border = BLACK;
	if (!minimap_tile_bounds(img, x, y, &rect))
		return ;
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
			int	px;
			int	py;
			bool	border_px;

			px = rect.x0 + i;
			py = rect.y0 + j;
			border_px = (j == 0 || j == height - 1
				|| i == 0 || i == width - 1);
			if (!border_px && block_color == 0)
				continue ;
			mlx_put_pixel(img, px, py,
				border_px ? border : (uint32_t)block_color);
		}
	}
}

static bool	minimap_tile_bounds(t_img *img, int tile_x, int tile_y, t_rect *rect)
{
	t_data	*data;
	double	tile_px;
	double	scale;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		img_w;
	int		img_h;

	data = get_data();
	tile_px = (double)data->tile_size;
	scale = data->mmp_scale;
	start_x = (int)lround(tile_px * scale * (double)tile_x);
	start_y = (int)lround(tile_px * scale * (double)tile_y);
	end_x = (int)lround(tile_px * scale * (double)(tile_x + 1));
	end_y = (int)lround(tile_px * scale * (double)(tile_y + 1));
	if (end_x <= start_x)
		end_x = start_x + 1;
	if (end_y <= start_y)
		end_y = start_y + 1;
	img_w = (int)img->width;
	img_h = (int)img->height;
	if (start_x >= img_w || start_y >= img_h)
		return (false);
	if (end_x > img_w)
		end_x = img_w;
	if (end_y > img_h)
		end_y = img_h;
	if (end_x <= start_x || end_y <= start_y)
		return (false);
	rect->x0 = start_x;
	rect->y0 = start_y;
	rect->x1 = end_x;
	rect->y1 = end_y;
	return (true);
}
