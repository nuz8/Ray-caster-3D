/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:07:21 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 03:00:53 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		init_rays(t_rays **rays);

static void	init_ray_delta(t_rays *ray, int num_rays, int i, t_data *data);
static void	init_ray_angle(t_rays *ray);
static void	init_ray_trig_coeffs(t_rays *ray, t_data *data);
static void	init_ray_state(t_rays *ray, t_data *data);

void	init_rays(t_rays **rays)
{
	t_data	*data;
	int		i;
	int		num_rays;
	t_rays	*ray;

	data = get_data();
	num_rays = data->num_rays;
	i = -1;
	while (++i < num_rays)
	{
		ray = rays[i];
		ray->index = i;
		init_ray_delta(ray, num_rays, i, data);
		ray->prev_dir = &data->prev_dir;
		ray->cur_dir = &data->cur_dir;
		init_ray_angle(ray);
		init_ray_trig_coeffs(ray, data);
		ray->length = ft_maxi(data->mmp_w, data->mmp_h) - 2 * data->tile_size;
		init_ray_state(ray, data);
	}
}

static void	init_ray_delta(t_rays *ray, int num_rays, int i, t_data *data)
{
	double	equi_delta;
	double	fov;
	int		fov2;

	fov = data->fov;
	fov2 = (int)fov / 2;
	equi_delta = fov / (double)(num_rays - 1);
	ray->delta = ((i * equi_delta - (double)fov2)) * PI / 180;
}

static void	init_ray_angle(t_rays *ray)
{
	double	ray_delta;
	double	cur_dir;
	double	pi2;

	ray_delta = ray->delta;
	cur_dir = *ray->cur_dir;
	pi2 = 2 * PI;
	ray->angle = cur_dir - ray_delta;
	if (ray->angle < 0)
		ray->angle += pi2;
	else if (ray->angle >= pi2)
		ray->angle -= pi2;
}

static void	init_ray_trig_coeffs(t_rays *ray, t_data *data)
{
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

static void	init_ray_state(t_rays *ray, t_data *data)
{
	ray->center_y = &data->pl_center_y;
	ray->center_x_d = &data->pl_center_x_d;
	ray->center_y_d = &data->pl_center_y_d;
	ray->hit_x = -1;
	ray->hit_y = -1;
	ray->inv_wall_distance = 0.0;
	ray->tex_u = 0.0;
}
