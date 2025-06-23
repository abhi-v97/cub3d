/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/23 18:49:33 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_gdata *gdata)
{
	gdata->map = NULL;
	gdata->map_height = 0;
	gdata->player.pos = player_get_pos_from_map(gdata);
	gdata->player_direction = 0;
	gdata->map_width = 0;
}

bool	init_graphics(t_gdata *gdata)
{
	gdata->ww = 1600;
	gdata->wh = 900;
	gdata->display = mlx_init();
	if (!gdata->display)
		return (false);
	gdata->win = mlx_new_window(gdata->display, gdata->ww, gdata->wh, "cub3D");
	if (!gdata->win)
		return (false);
	gdata->cnvs.img = mlx_new_image(gdata->display, gdata->ww, gdata->wh);
	gdata->cnvs.addr = mlx_get_data_addr(gdata->cnvs.img, &gdata->cnvs.bpp, \
		&gdata->cnvs.ll, &gdata->cnvs.endian);
	gdata->cnvs.w = gdata->ww;
	gdata->cnvs.h = gdata->wh;
	init_data(gdata);
	return (true);
}