/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 06:10:15 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 06:14:53 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_border_pixel(int x, int y, int width, int height)
{
	if (y == 0 || y == height - 1)
		return (true);
	if (x == 0 || x == width - 1)
		return (true);
	return (false);
}

double	tile_step(void)
{
	t_data	*data;

	data = get_data();
	return ((double)data->tile_size * data->mmp_scale);
}

void	init_tile_edges(double step, int tile, int *start, int *end)
{
	*start = (int)lround(step * (double)tile);
	*end = (int)lround(step * (double)(tile + 1));
	if (*end <= *start)
		*end = *start + 1;
}

bool	validate_edge(int *start, int *end, int max)
{
	if (*start >= max)
		return (false);
	if (*end > max)
		*end = max;
	if (*end <= *start)
		return (false);
	return (true);
}
