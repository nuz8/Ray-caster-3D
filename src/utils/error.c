/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:08:00 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/09/29 17:53:29 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	exit_early(t_game *game, char *msg, int ret);
static void	clear_map(t_game *game, t_map *map);
static void	clear_player(t_game *game, t_player *pl);
static void	clear_mlx(t_game *game);


void	exit_early(t_game *game, char *msg, int ret)
{
	if (msg)
		perror(msg);
	if (!game)
		exit(ret);

	if (game->mlx && game->map)
		clear_map(game, game->map);
	if (game->mlx && game->player)
		clear_player(game, game->player);
	if (game->mlx)
		clear_mlx(game);

	main_cleanup(ret);
}

static void	clear_map(t_game *game, t_map *map)
{
	if (map->image)
		mlx_delete_image(game->mlx, map->image);
	if (!(map->fd < 0))
		close(map->fd);
}

static void	clear_player(t_game *game, t_player *pl)
{
	if (pl->blob2D)
		mlx_delete_image(game->mlx, pl->blob2D);
	if (pl->view)
		mlx_delete_image(game->mlx, pl->view);
}

static void	clear_mlx(t_game *game)
{
	if (game->mlx)	// still experimental
	{
		if (game->background)
			mlx_delete_image(game->mlx, game->background);
		if (game->img3D)
			mlx_delete_image(game->mlx, game->img3D);
		mlx_close_window(game->mlx);	// close a window if it is open to free the resources, mlx instance stays allocated
		mlx_terminate(game->mlx);		// terminate the mlx instance by freeing the allocation
	}
}

void	free_exit_early(t_game *game, char *msg, int ret, char *str)
{
	free(str);
	exit_early(game, msg, ret);
}
