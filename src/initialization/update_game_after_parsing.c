/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game_after_parsing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 23:50:48 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 02:43:29 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	update_player_metrics(t_data *data)
{
	data->cosine = cos(data->cur_dir);
	data->sine = sin(data->cur_dir);
	data->mmp_w = data->tiles_x * data->tile_size;
	data->mmp_h = data->tiles_y * data->tile_size;
	data->pl_center_x = data->pl_posx + data->tile_size / 2;
	data->pl_center_y = data->pl_posy + data->tile_size / 2;
	data->pl_posx_d = data->pl_posx;
	data->pl_posy_d = data->pl_posy;
	data->pl_center_x_d = data->pl_center_x;
	data->pl_center_y_d = data->pl_center_y;
	if (data->tile_size > 0)
		data->inv_tile_size = 1.0 / (double)data->tile_size;
}

static double	compute_minimap_scale(t_data *data)
{
	double	scale_w;
	double	scale_h;
	double	scale;
	double	max_scale;

	scale_w = (double)MMP_W / (double)data->mmp_w;
	scale_h = (double)MMP_H / (double)data->mmp_h;
	scale = fmin(scale_w, scale_h);
	max_scale = (double)MINIMAP_TILE_MAX / (double)data->tile_size;
	if (scale > max_scale)
		scale = max_scale;
	if (scale <= 0.0)
		scale = (double)MINIMAP_TILE_MIN / (double)data->tile_size;
	if (scale <= 0.0)
		scale = 1.0;
	return (scale);
}

static void	apply_minimap_scale(t_data *data, double scale)
{
	data->mmp_scale = scale;
	if (data->mmp_scale <= 0.0)
		data->mmp_scale = 1.0;
	data->mmp_inv_scale = 1.0 / data->mmp_scale;
	data->mmp_disp_w = ft_maxi(1, (int)lround((double)data->mmp_w
				* data->mmp_scale));
	data->mmp_disp_h = ft_maxi(1, (int)lround((double)data->mmp_h
				* data->mmp_scale));
	data->mm_tile_size = ft_maxi(1, (int)lround((double)data->tile_size
				* data->mmp_scale));
	data->pl_dia_mm = ft_maxi(2, (int)lround((double)data->pl_dia
				* data->mmp_scale));
	data->pl_dir_len_mm = ft_maxi(1, (int)lround((double)PL_DIR_LEN
				* data->mmp_scale));
}

static void	set_minimap_defaults(t_data *data)
{
	data->mmp_scale = 1.0;
	data->mmp_inv_scale = 1.0;
	data->mm_tile_size = data->tile_size;
	data->mmp_disp_w = ft_maxi(1, data->mmp_w);
	data->mmp_disp_h = ft_maxi(1, data->mmp_h);
	data->pl_dia_mm = data->pl_dia;
	data->pl_dir_len_mm = PL_DIR_LEN;
}

void	update_game_data_after_parsing(t_data *data)
{
	double	scale;

	update_player_metrics(data);
	if (data->tiles_x > 0 && data->tiles_y > 0 && data->mmp_w > 0
		&& data->mmp_h > 0 && data->tile_size > 0)
	{
		scale = compute_minimap_scale(data);
		apply_minimap_scale(data, scale);
	}
	else
		set_minimap_defaults(data);
}
