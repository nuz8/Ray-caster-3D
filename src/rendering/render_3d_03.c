/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdemiroz <sdemiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 08:20:17 by sdemiroz          #+#    #+#             */
/*   Updated: 2025/10/07 08:20:17 by sdemiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint32_t	column_sample_color(t_column_ctx *ctx, int tex_y)
{
	size_t	offset;
	uint8_t	*pixels;

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= (int)ctx->texture->height)
		tex_y = ctx->texture->height - 1;
	pixels = ctx->texture->pixels;
	offset = ((size_t)tex_y * ctx->texture->width + (size_t)ctx->tex_x)
		* ctx->texture->bytes_per_pixel;
	return ((pixels[offset] << 24) | (pixels[offset + 1] << 16)
		| (pixels[offset + 2] << 8) | pixels[offset + 3]);
}

void	column_write_texel(t_column_ctx *ctx, int y, uint32_t color)
{
	size_t	offset;

	offset = ((size_t)y * ctx->width + (size_t)ctx->screen_x) * 4;
	ctx->dst[offset] = (color >> 24) & 0xFF;
	ctx->dst[offset + 1] = (color >> 16) & 0xFF;
	ctx->dst[offset + 2] = (color >> 8) & 0xFF;
	ctx->dst[offset + 3] = color & 0xFF;
}
