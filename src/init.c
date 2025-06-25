/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/25 14:29:47 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data(t_gdata *gdata);
static bool	init_graphics(t_gdata *gdata);

bool	init_all(t_gdata *gdata)
{
	if (!init_graphics(gdata))
		return (false);
	init_data(gdata);
	return (true);
}

static void	init_data(t_gdata *gdata)
{
	gdata->map = NULL;
	gdata->map_height = 0;
	gdata->player.pos = player_get_pos_from_map(gdata);
	gdata->player_direction = 0;
	gdata->map_width = 0;
}

bool	init_graphics(t_gdata *gdata)
{
	gdata->ww = W_WIDTH;
	gdata->wh = W_HEIGHT;
	gdata->display = mlx_init();
	if (!gdata->display)
		return (gdata->exit_code = EMLXERR, false);
	gdata->win = mlx_new_window(gdata->display, gdata->ww, gdata->wh, "cub3D");
	if (!gdata->win)
		return (gdata->exit_code = EMLXWINERR, false);
	gdata->cnvs.img = mlx_new_image(gdata->display, gdata->ww, gdata->wh);
	gdata->cnvs.addr = mlx_get_data_addr(gdata->cnvs.img, &gdata->cnvs.bpp, \
		&gdata->cnvs.ll, &gdata->cnvs.endian);
	gdata->cnvs.w = gdata->ww;
	gdata->cnvs.h = gdata->wh;
	return (true);
}
