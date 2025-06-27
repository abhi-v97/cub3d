/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/26 14:05:35 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	init_graphics(t_gdata *gdata);

int	init_gdata(t_gdata *gdata)
{
	gdata->map = NULL;
	gdata->map_height = 0;
	gdata->player.pos.x = 0.0;
	gdata->player.pos.y = 0.0;
	gdata->player_direction = 0;
	gdata->map_width = 0;
	gdata->tex_rgb = ft_calloc(sizeof(int), 7);
	gdata->textures = ft_calloc(sizeof(int *), 7);
	if (!init_graphics(gdata))
		return (1);
	return (0);
}

static bool	init_graphics(t_gdata *gdata)
{
	gdata->ww = 1600;
	gdata->wh = 900;
	gdata->mlx = mlx_init();
	if (!gdata->mlx)
		return (false);
	gdata->win = mlx_new_window(gdata->mlx, gdata->ww, gdata->wh, "cub3D");
	if (!gdata->win)
		return (free(gdata->mlx), false);
	gdata->cnvs.img = mlx_new_image(gdata->mlx, gdata->ww, gdata->wh);
	gdata->cnvs.addr = mlx_get_data_addr(gdata->cnvs.img, &gdata->cnvs.bpp, \
		&gdata->cnvs.ll, &gdata->cnvs.endian);
	gdata->cnvs.w = gdata->ww;
	gdata->cnvs.h = gdata->wh;
	return (true);
}
