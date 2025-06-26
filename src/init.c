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

void	init_gdata(t_gdata *gdata);
bool	init_graphics(t_gdata *gdata);

void	init_gdata(t_gdata *gdata)
{
	gdata->map = NULL;
	gdata->map_height = 0;
	gdata->player.pos = pos_init_to_invalid_pos();
	gdata->player_direction = 0;
	gdata->map_width = 0;
	memset(gdata->keys, 0, sizeof(int) * KEY_COUNT);
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
	gdata->canvas.img = mlx_new_image(gdata->display, gdata->ww, gdata->wh);
	gdata->canvas.addr = mlx_get_data_addr(gdata->canvas.img, &gdata->canvas.bpp, \
		&gdata->canvas.ll, &gdata->canvas.endian);
	gdata->canvas.w = gdata->ww;
	gdata->canvas.h = gdata->wh;
	return (true);
}
