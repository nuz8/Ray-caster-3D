/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:27:37 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 02:46:47 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_player(t_game *game)
{
	t_data		*data;
	t_player	*pl;

	data = game->data;
	pl = game->player;
	pl->data = data;
	pl->blob_2d = mlx_new_image(game->mlx, ft_maxi(1, data->mm_tile_size),
			ft_maxi(1, data->mm_tile_size));
	if (!pl->blob_2d)
		exit_early(game, "blob_img: mlx_new_image failed", EXIT_FAILURE);
	pl->view = mlx_new_image(game->mlx, data->mmp_disp_w, data->mmp_disp_h);
	if (!pl->view)
		exit_early(game, "view_img: mlx_new_image failed", EXIT_FAILURE);
	pl->rays = get_rays();
	if (!pl->rays)
		exit_early(game, "rays malloc failed", EXIT_FAILURE);
	init_rays(pl->rays);
	pl->game = game;
	pl->map = game->map;
}

void	init_background(t_game *game)
{
	int			x;
	int			y;
	uint32_t	ceiling;
	uint32_t	floor;

	y = 0;
	ceiling = (game->ceiling_color.r << 24) | (game->ceiling_color.g << 16)
		| (game->ceiling_color.b << 8) | 0xFF;
	floor = (game->floor_color.r << 24) | (game->floor_color.g << 16)
		| (game->floor_color.b << 8) | 0xFF;
	while (y < game->data->wind_h)
	{
		x = 0;
		while (x < game->data->wind_w)
		{
			if (y < game->data->wind_h / 2)
				mlx_put_pixel(game->background, x, y, ceiling);
			else
				mlx_put_pixel(game->background, x, y, floor);
			x++;
		}
		y++;
	}
}

static void	init_minimap(t_game *game, char *path_to_map)
{
	t_data	*data;
	t_map	*map;

	data = game->data;
	map = game->map;
	map->data = data;
	parse_game_data(game, path_to_map);
	update_game_data_after_parsing(data);
	init_background(game);
	create_image_array(map, data);
	map->image = mlx_new_image(game->mlx, data->mmp_disp_w, data->mmp_disp_h);
	if (!map->image)
		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);
	map->test = mlx_new_image(game->mlx, data->mmp_disp_w, data->mmp_disp_h);
	if (!map->test)
		exit_early(game, "map_img: mlx_new_image failed", EXIT_FAILURE);
	map->game = game;
	map->player = game->player;
}

static void	init_game(t_game *game)
{
	t_data	*data;

	*game = (t_game){
		.background_inst_id = -1,
		.img_3d_inst_id = -1,
	};
	data = get_data();
	if (!data)
		exit_early(game, "Scales malloc failed", EXIT_FAILURE);
	game->data = data;
	game->mlx = mlx_init(data->wind_w, data->wind_h, "Cub3D", true);
	if (!game->mlx)
		exit_early(game, "game_mlx: mlx_init", EXIT_FAILURE);
	data->time = mlx_get_time();
	data->acc_time = data->time;
	game->background = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!game->background)
		exit_early(game, "background_img: mlx_new_image", EXIT_FAILURE);
	game->img_3d = mlx_new_image(game->mlx, data->wind_w, data->wind_h);
	if (!game->img_3d)
		exit_early(game, "game_img_3d: mlx_new_image", EXIT_FAILURE);
}

void	init_game_elements(t_game *game, char *arg)
{
	init_game(game);
	game->map = get_map();
	if (!game->map)
		exit_early(game, "map: struct malloc failed", EXIT_FAILURE);
	game->player = get_player();
	if (!game->player)
		exit_early(game, "player malloc failed", EXIT_FAILURE);
	init_minimap(game, arg);
	init_player(game);
}
