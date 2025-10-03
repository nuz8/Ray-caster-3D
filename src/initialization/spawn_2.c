/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:59:46 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/04 00:00:22 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_rays	**get_rays(void)
{
	static t_rays	**rays = NULL;
	int				i;
	int				num_rays;

	if (!rays)
	{
		num_rays = get_data()->num_rays;
		rays = ft_malloc((num_rays + 1) * sizeof(t_rays *));
		if (rays)
		{
			i = -1;
			while (++i < num_rays)
			{
				rays[i] = ft_malloc(sizeof(t_rays));
				if (rays[i])
				{
					*rays[i] = (t_rays){
						.index = i,
					};
				}
			}
		}
		rays[num_rays] = NULL;
	}
	return (rays);
}
