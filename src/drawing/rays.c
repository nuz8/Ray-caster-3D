/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:51:11 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 04:02:26 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline int	world_to_minimap(double value, double scale)
{
	return ((int)lround(value * scale));
}

static void			minimap_plot_ray(t_player *pl, t_rays *ray,
						uint32_t colour);

void				draw_player_direction(t_player *pl, t_data *data);
void				erase_prev_direction(t_player *pl, t_data *data);
void				draw_cur_direction(t_player *pl, t_data *data);

void				erase_previous_fov(t_player *pl, t_rays **rays);
void				erase_ray(t_player *pl, t_rays *ray);

void				draw_current_fov(t_player *pl, t_rays **rays);
void				draw_ray(t_player *pl, t_rays *ray);

void				udpate_rays(t_rays **rays, t_map *map, t_data *data);
static void			update_ray_attr(t_rays *ray, t_data *data);

void	draw_player_direction(t_player *pl, t_data *data)
{
	if (data->prev_dir != data->cur_dir)
		erase_prev_direction(pl, data);
	draw_cur_direction(pl, data);
}

void	erase_prev_direction(t_player *pl, t_data *data)
{
	double	scale;
	double	world_center_x;
	double	world_center_y;
	int		width;
	int		height;
	int		step;
		double world_x;
		double world_y;
		int ix;
		int iy;

	if (!pl->view)
		return ;
	scale = data->mmp_scale;
	world_center_x = data->pl_center_x_d;
	world_center_y = data->pl_center_y_d;
	width = (int)pl->view->width;
	height = (int)pl->view->height;
	step = 0;
	while (step++ < PL_DIR_LEN)
	{
		world_x = world_center_x + step * data->cosine;
		world_y = world_center_y - step * data->sine;
		ix = world_to_minimap(world_x, scale);
		iy = world_to_minimap(world_y, scale);
		if (ix >= 0 && ix < width && iy >= 0 && iy < height)
			mlx_put_pixel(pl->view, ix, iy, RESET);
	}
}

void	draw_cur_direction(t_player *pl, t_data *data)
{
	double	scale;
	double	world_center_x;
	double	world_center_y;
	int		width;
	int		height;
	int		step;
		double world_x;
		double world_y;
		int ix;
		int iy;

	if (!pl->view)
		return ;
	data->sine = sin(data->cur_dir);
	data->cosine = cos(data->cur_dir);
	scale = data->mmp_scale;
	world_center_x = data->pl_center_x_d;
	world_center_y = data->pl_center_y_d;
	width = (int)pl->view->width;
	height = (int)pl->view->height;
	step = 0;
	while (step++ < PL_DIR_LEN)
	{
		world_x = world_center_x + step * data->cosine;
		world_y = world_center_y - step * data->sine;
		ix = world_to_minimap(world_x, scale);
		iy = world_to_minimap(world_y, scale);
		if (ix >= 0 && ix < width && iy >= 0 && iy < height)
			mlx_put_pixel(pl->view, ix, iy, RED);
	}
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

static void	minimap_plot_ray(t_player *pl, t_rays *ray, uint32_t colour)
{
	t_data	*data;
	double	scale;
	double	start_x;
	double	start_y;
	double	cos_v;
	double	sin_v;
	int		width;
	int		height;
	int		steps;
	int		i;
	int		prev_ix;
	int		prev_iy;
	bool	first;
		double world_x;
		double world_y;
		int ix;
		int iy;

	if (!pl || !pl->view || !ray)
		return ;
	data = pl->data;
	scale = data->mmp_scale;
	width = (int)pl->view->width;
	height = (int)pl->view->height;
	start_x = *ray->center_x_d;
	start_y = *ray->center_y_d;
	cos_v = ray->cosine;
	sin_v = ray->sine;
	if (ray->length <= 0.0 || width <= 0 || height <= 0)
		return ;
	steps = ft_maxi(1, (int)ceil(ray->length));
	first = true;
	prev_ix = 0;
	prev_iy = 0;
	i = -1;
	while (++i <= steps)
	{
		world_x = start_x + i * cos_v;
		world_y = start_y - i * sin_v;
		ix = world_to_minimap(world_x, scale);
		iy = world_to_minimap(world_y, scale);
		if (!first && ix == prev_ix && iy == prev_iy)
			continue ;
		first = false;
		prev_ix = ix;
		prev_iy = iy;
		if (ix >= 0 && ix < width && iy >= 0 && iy < height)
			mlx_put_pixel(pl->view, ix, iy, colour);
	}
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
