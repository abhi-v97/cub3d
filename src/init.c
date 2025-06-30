/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 22:16:25 by aistok           ###   ########.fr       */
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
	memset(gdata->keys, 0, KEY_COUNT * sizeof(int));
	memset(gdata->mbutt, 0, M_BUTT_COUNT * sizeof(int));
	gdata->win_center.x = W_WIDTH / 2;
	gdata->win_center.y = W_HEIGHT / 2;
	gdata->time = 0;
	gdata->old_time = 0;
	if (!init_graphics(gdata))
		return (1);
	return (0);
}

static bool	init_graphics(t_gdata *gdata)
{
	gdata->mlx = mlx_init();
	if (!gdata->mlx)
		return (false);
	gdata->win = mlx_new_window(gdata->mlx, W_WIDTH, W_HEIGHT, "cub3D");
	if (!gdata->win)
		return (free(gdata->mlx), false);
	gdata->canvas.img = mlx_new_image(gdata->mlx, W_WIDTH, W_HEIGHT);
	gdata->canvas.addr = mlx_get_data_addr(gdata->canvas.img, &gdata->canvas.bpp,
			&gdata->canvas.ll, &gdata->canvas.endian);
	gdata->canvas.w = W_WIDTH;
	gdata->canvas.h = W_HEIGHT;
	mlx_mouse_move(gdata->mlx, gdata->win, gdata->win_center.x, gdata->win_center.y);
	mlx_mouse_get_pos(gdata->mlx, gdata->win, &gdata->mpos_at_start.x, &gdata->mpos_at_start.y);
	return (true);
}
