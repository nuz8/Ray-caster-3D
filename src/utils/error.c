/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:08:00 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 13:40:34 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void		exit_early(t_game *game, char *msg, int ret);
static void	clear_map(t_game *game, t_map *map);
static void	clear_player(t_game *game, t_player *pl);
static void	clear_mlx(t_game *game);

void	exit_early(t_game *game, char *msg, int ret)
{
	if (msg)
		perror(msg);
	if (!game)
		exit(ret);
	if (game->no_texture && game->no_texture)
		mlx_delete_texture(game->no_texture);
	if (game->so_texture && game->so_texture)
		mlx_delete_texture(game->so_texture);
	if (game->we_texture && game->we_texture)
		mlx_delete_texture(game->we_texture);
	if (game->ea_texture && game->ea_texture)
		mlx_delete_texture(game->ea_texture);
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
	if (pl->blob_2d)
		mlx_delete_image(game->mlx, pl->blob_2d);
	if (pl->view)
		mlx_delete_image(game->mlx, pl->view);
}

static void	clear_mlx(t_game *game)
{
	if (game->mlx)
	{
		if (game->background)
			mlx_delete_image(game->mlx, game->background);
		if (game->img_3d)
			mlx_delete_image(game->mlx, game->img_3d);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
}

void	free_exit_early(t_game *game, char *msg, int ret, char *str)
{
	free(str);
	exit_early(game, msg, ret);
}
