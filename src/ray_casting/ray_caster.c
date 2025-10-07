/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 15:33:10 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/07 04:18:15 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	cast_rays(t_map *map, t_rays **rays, t_data *data);

static void	calculate_ray_length(t_game *game, t_rays *ray, char **img,
		t_data *data);
static void	update_distance(t_dvec *hype, t_ivec *check);
static void extract_xy(t_rays *ray, double distance, t_ivec *ptr[], t_dvec hop,
		t_dvec start);
static void	assign_wall_texture(t_game *game, t_rays *ray, t_dvec hop,
		t_ivec check);

void	cast_rays(t_map *map, t_rays **rays, t_data *data)
{
	t_game	*game;
	char	**img;
	int		total_rays;
	int		i;

	game = map->game;
	img = map->img_array;
	total_rays = data->num_rays;
	i = -1;
	while (++i < total_rays)
		calculate_ray_length(game, rays[i], img, data);
}

static void	calculate_ray_length(t_game *game, t_rays *ray, char **img,
		t_data *data)
{
	t_dvec	hop;
	t_dvec	hype[3];								
	t_ivec	check;
	t_ivec	hit;
	t_dvec	start;
	double	inv_tile_size;

	start.x = *ray->center_x_d;
	start.y = *ray->center_y_d;
	ray->inv_wall_distance = 0.0;
	ray->tex_u = 0.0;
	inv_tile_size = data->inv_tile_size;
	if (inv_tile_size <= 0.0 && data->tile_size > 0)
		inv_tile_size = 1.0 / (double)data->tile_size;
	initialize_ray_caster(ray, data, (t_dvec *[]){&hop, hype}, &check);
	while (hype[2].x <= hype[2].y)
	{
		update_distance(hype, &check);
		extract_xy(ray, hype[2].x, (t_ivec *[]){&hit, &check}, hop, start);
		if ((hit.x >= 0 && hit.x < data->mmp_w && hit.y >= 0 &&
				hit.y < data->mmp_h) && (img[hit.y][hit.x] == '1'))
		{
				ray->length = (hype[2].x);
				ray->wall_distance = ((hype[2].x) * cos(ray->delta));
				if (ray->wall_distance > 1e-6)
					ray->inv_wall_distance = 1.0 / ray->wall_distance;
				ray->hit_x = start.x + hype[2].x * ray->cosine;
				ray->hit_y = start.y - hype[2].x * ray->sine;
				assign_wall_texture(game, ray, hop, check);
				if (ray->hit_wall == 'N' || ray->hit_wall == 'S')
				{
					double	tile_pos;
					tile_pos = ray->hit_x * inv_tile_size;
					ray->tex_u = tile_pos - floor(tile_pos);
				}
				else
				{
					double	tile_pos;
					tile_pos = ray->hit_y * inv_tile_size;
					ray->tex_u = tile_pos - floor(tile_pos);
				}
				if (ray->tex_u < 0.0)
					ray->tex_u += 1.0;
				break ;
			}
		}
}

static void	update_distance(t_dvec *hype, t_ivec *check)
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

static void extract_xy(t_rays *ray, double distance, t_ivec *ptr[], t_dvec hop,
		t_dvec start)
{
	t_ivec	*hit;
	t_ivec	*check;
	double	hx;
	double	hy;

	hit = *ptr;
	check = *(ptr + 1);
	hx = start.x + distance * ray->cosine;
	hy = start.y - distance * ray->sine;
	hit->x = (int)hx;
	hit->y = (int)hy;
	if (check->x)
	{
		if (hop.x < 0)
			hit->x--;
		else
			hit->x++;
	}
	else if (check->y)
	{
		if (hop.y < 0)
			hit->y--;
		else
			hit->y++;
	}
}

static void	assign_wall_texture(t_game *game, t_rays *ray, t_dvec hop, t_ivec check)
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
