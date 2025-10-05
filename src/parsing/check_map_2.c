/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 20:58:06 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/05 20:58:39 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	empty_line(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_isspace(line[x]) && line[x] != '\n')
			return (false);
		x++;
	}
	return (true);
}

void	assign_direction(t_map *map, char player_dir)
{
	t_data	*data;

	data = map->data;
	data->ini_dir = player_dir;
	if (player_dir == 'E')
		data->cur_dir = 0;
	else if (player_dir == 'N')
		data->cur_dir = PI / 2;
	else if (player_dir == 'W')
		data->cur_dir = PI;
	else if (player_dir == 'S')
		data->cur_dir = -PI / 2;
}
