/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 21:13:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/04 00:02:27 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	initialize_rest_data(t_data *data)
{
	data->mmp_w = 0;
	data->mmp_h = 0;
	data->mmp_offx = MAP_OFFSET_X;
	data->mmp_offy = MAP_OFFSET_Y;
	data->mmp_scale = 1.0;
	data->mmp_inv_scale = 1.0;
	data->mm_tile_size = TILE_SIZE;
	data->mmp_disp_w = 0;
	data->mmp_disp_h = 0;
	data->tile_size = TILE_SIZE;
	if (TILE_SIZE > 0)
		data->inv_tile_size = 1.0 / (double)TILE_SIZE;
	data->tiles_x = 0;
	data->tiles_y = 0;
	data->fov_toggle = true;
	data->pl_dia_mm = data->pl_dia;
	data->pl_dir_len_mm = PL_DIR_LEN;
	data->fps = 0;
	data->time = 0;
	data->acc_time = 0;
	data->debug_offset_x = 0;
	data->debug_offset_y = 0;
}

static void	init_data_values(t_data *data)
{
	data->wind_w = WIDTH;
	data->wind_h = HEIGHT;
	data->pl_dia = PLAYER_DIA;
	data->pl_posx = START_PX;
	data->pl_posy = START_PY;
	data->pl_center_x = START_PX + TILE_SIZE / 2;
	data->pl_center_y = START_PY + TILE_SIZE / 2;
	data->pl_posx_d = data->pl_posx;
	data->pl_posy_d = data->pl_posy;
	data->pl_center_x_d = data->pl_center_x;
	data->pl_center_y_d = data->pl_center_y;
	data->inv_tile_size = 1.0 / (double)TILE_SIZE;
	data->fov = FOV;
	data->num_rays = NUM_RAYS;
	data->ini_dir = 'N';
	data->prev_dir = PI / 2;
	data->cur_dir = PI / 2;
	data->cosine = cos(PI / 2);
	data->sine = sin(PI / 2);
	initialize_rest_data(data);
}

t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (!data)
	{
		data = ft_malloc(sizeof(t_data));
		if (data)
			init_data_values(data);
	}
	return (data);
}

t_map	*get_map(void)
{
	static t_map	*map = NULL;

	if (!map)
	{
		map = ft_malloc(sizeof(t_map));
		if (map)
		{
			map->data = NULL;
			map->image = NULL;
			map->image_inst_id = -1;
			map->fd = -1;
			map->map_array = NULL;
			map->img_array = NULL;
			map->game = NULL;
			map->player = NULL;
		}
	}
	return (map);
}

t_player	*get_player(void)
{
	static t_player	*player = NULL;

	if (!player)
	{
		player = ft_malloc(sizeof(t_player));
		if (player)
		{
			player->data = NULL;
			player->blob2D = NULL;
			player->blob_inst_id = -1;
			player->view = NULL;
			player->view_inst_id = -1;
			player->game = NULL;
			player->map = NULL;
			player->rays = NULL;
		}
	}
	return (player);
}
