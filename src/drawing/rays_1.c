/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:51:11 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 06:41:05 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_current_fov(t_player *pl, t_rays **rays)
{
	int	num_rays;
	int	i;

	if (pl->data->fov_toggle == false)
		return ;
	num_rays = pl->data->num_rays;
	i = -1;
	while (++i < num_rays)
	{
		if (rays[i])
			draw_ray(pl, rays[i]);
	}
}

void	draw_ray(t_player *pl, t_rays *ray)
{
	minimap_plot_ray(pl, ray, DEBUG_GREEN2);
}

static void	update_ray_attr(t_rays *ray, t_data *data)
{
	double	pi2;

	pi2 = 2 * PI;
	ray->angle = *ray->cur_dir - ray->delta;
	if (ray->angle < 0)
		ray->angle += pi2;
	else if (ray->angle >= pi2)
		ray->angle -= pi2;
	ray->cosine = cos(ray->angle);
	ray->sine = sin(ray->angle);
	if (fabs(ray->cosine) > 1e-6)
		ray->coeff.x = 1 / ray->cosine;
	else
		ray->coeff.x = data->mmp_w;
	if (fabs(ray->sine) > 1e-6)
		ray->coeff.y = 1 / ray->sine;
	else
		ray->coeff.y = data->mmp_h;
}

void	minimap_plot_ray(t_player *pl, t_rays *ray, uint32_t colour)
{
	t_ray_ctx	ctx;

	if (!init_ray_ctx(pl, ray, &ctx))
		return ;
	plot_ray_pixels(pl, &ctx, colour);
}

void	udpate_rays(t_rays **rays, t_map *map, t_data *data)
{
	t_rays	*ray;
	int		i;
	int		num_rays;

	num_rays = data->num_rays;
	i = -1;
	while (++i < num_rays)
	{
		ray = rays[i];
		update_ray_attr(ray, data);
	}
	cast_rays(map, rays, data);
}
