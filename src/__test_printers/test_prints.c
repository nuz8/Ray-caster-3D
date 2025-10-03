/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_prints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 02:20:03 by pamatya           #+#    #+#             */
/*   Updated: 2025/10/03 23:11:38 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	test_print_rays(char c);


void	test_print_rays(char c)
{
	t_rays	**rays;
	int		i;

	rays = get_player()->rays;
	printf("Rays:\n");
	i = -1;
	if (c == 'r')	// print angles in radians
	{
		while (rays[++i])
		{
			// printf("Ray %d:\n", i);
			// printf("  Delta: %.3f\n", rays[i]->delta);
			// printf("  Prev Dir: %.3f\n", *rays[i]->prev_dir);
			// printf("  Cur Dir: %.3f\n", *rays[i]->cur_dir);
			// printf("  Angle: %.3f\n", rays[i]->angle);
			// printf("  Cosine: %.3f\n", rays[i]->cosine);
			// printf("  Sine: %.3f\n", rays[i]->sine);
			// printf("  Center X: %d\n", *rays[i]->center_x);
			// printf("  Center Y: %d\n", *rays[i]->center_y);
			// printf("  Hit X: %d\n", rays[i]->hit_x);
			// printf("  Hit Y: %d\n", rays[i]->hit_y);
			// printf("  Length: %.3f\n", rays[i]->length);
			
			printf("Ray %d:\t", i);
			// printf("  Prev Dir: %.3f\t", *rays[i]->prev_dir);
			printf("  Cur Dir: %.3f\t", *rays[i]->cur_dir);
			printf("  Delta: %.3f\t", rays[i]->delta);
			printf("  Angle: %.3f\t", rays[i]->angle);
			// printf("  Cosine: %.3f\t", rays[i]->cosine);
			// printf("  Sine: %.3f\t", rays[i]->sine);
			printf("  Center X: %d\t", *rays[i]->center_x);
			printf("  Center Y: %d\t", *rays[i]->center_y);
			printf("  Hit X: %.2f\t", rays[i]->hit_x);
			printf("  Hit Y: %.2f\t", rays[i]->hit_y);
			printf("  Length: %.3f\n", rays[i]->length);
		}
	}
	else if (c == 'd') // print angles in degrees
	{
		while (rays[++i])
		{
			// printf("Ray %d:\n", i);
			// printf("  Delta: %.3f\n", rays[i]->delta * (180 / PI));
			// printf("  Prev Dir: %.3f\n", *rays[i]->prev_dir * (180 / PI));
			// printf("  Cur Dir: %.3f\n", *rays[i]->cur_dir * (180 / PI));
			// printf("  Angle: \033[0;31m%.3f\n\033[0m", rays[i]->angle * (180 / PI));
			// printf("  Cosine: %.3f\n", rays[i]->cosine);
			// printf("  Sine: %.3f\n", rays[i]->sine);
			// printf("  Center X: %d\n", *rays[i]->center_x);
			// printf("  Center Y: %d\n", *rays[i]->center_y);
			// printf("  Hit X: %d\n", rays[i]->hit_x);
			// printf("  Hit Y: %d\n", rays[i]->hit_y);
			// printf("  Length: %.3f\n", rays[i]->length);
			
			printf("Ray %d: \t", i);
			// printf("  Prev Dir: %.3f\t", *rays[i]->prev_dir * (180 / PI));
			printf("  Cur Dir: %.3f\t", *rays[i]->cur_dir * (180 / PI));
			printf("  Delta: %.3f  \t", rays[i]->delta * (180 / PI));
			printf("  Angle: \033[0;31m%.3f  \t\033[0m", rays[i]->angle * (180 / PI));
			// printf("  Cosine: %.3f\t", rays[i]->cosine);
			// printf("  Sine: %.3f\t", rays[i]->sine);
			printf("  Center X: %d  ", *rays[i]->center_x);
			printf("  Center Y: %d\t", *rays[i]->center_y);
			printf("  Hit X: %.2f  ", rays[i]->hit_x);
			printf("  Hit Y: %.2f\t", rays[i]->hit_y);
			printf("  Length: %.d\t", (int)rays[i]->length);

			double	dx = rays[i]->hit_x - *rays[i]->center_x;
			double	dy = rays[i]->hit_y - *rays[i]->center_y;
			double	len = sqrt((dx * dx) + (dy * dy));
			printf("  Correct length: %d\t", (int)len);
			printf("  del_len: %d\n", (int)(len - rays[i]->length));
			// printf("  dx: %d\tdy: %d\n", (int)dx, (int)dy);
		}
	}
	else
		printf("Invalid argument for test_print_rays. Use 'r' for radians or 'd' for degrees.\n");
}

void	test_print_bounds(int *boundx, int *boundy)
{
	printf("boundx1 = %d\t", boundx[0]);
	printf("boundx2 = %d\n", boundx[1]);
	printf("boundy1 = %d\t", boundy[0]);
	printf("boundy2 = %d\n", boundy[1]);
}
