/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 06:28:29 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 06:58:23 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	erase_prev_direction(t_player *pl, t_data *data)
{
	t_dir_ctx	ctx;

	if (!init_direction_ctx(pl, data, data->prev_dir, &ctx))
		return ;
	draw_direction_line(pl, &ctx, RESET);
}

void	draw_player_direction(t_player *pl, t_data *data)
{
	if (data->prev_dir != data->cur_dir)
		erase_prev_direction(pl, data);
	draw_cur_direction(pl, data);
}

void	draw_cur_direction(t_player *pl, t_data *data)
{
	t_dir_ctx	ctx;

	if (!init_direction_ctx(pl, data, data->cur_dir, &ctx))
		return ;
	draw_direction_line(pl, &ctx, RED);
	data->sine = ctx.sine;
	data->cosine = ctx.cosine;
}

void	erase_previous_fov(t_player *pl, t_rays **rays)
{
	int	num_rays;
	int	i;

	if (pl->data->fov_toggle == false)
		return ;
	num_rays = pl->data->num_rays;
	i = -1;
	while (++i < num_rays)
		erase_ray(pl, rays[i]);
}

void	erase_ray(t_player *pl, t_rays *ray)
{
	minimap_plot_ray(pl, ray, RESET);
}
