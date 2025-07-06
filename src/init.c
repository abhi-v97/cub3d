/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/07/06 13:17:21 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_graphics_has_error(t_gdata *gd);

int	init_gdata_has_error(t_gdata *gd)
{
	gd->map = NULL;
	gd->map_height = 0;
	gd->map_width = 0;
	gd->player.pos.x = 0.0;
	gd->player.pos.y = 0.0;
	gd->player_direction = 0;
	gd->tex_rgb = ft_calloc(sizeof(int), 7);
	if (!gd->tex_rgb)
		return (gd->exit_status = ENOMEM);
	gd->textures = ft_calloc(sizeof(int *), 7);
	if (!gd->textures)
		return (free(gd->tex_rgb), gd->exit_status = ENOMEM);
	memset(gd->keys, 0, KEY_COUNT * sizeof(int));
	gd->win_center.x = W_WIDTH / 2;
	gd->win_center.y = W_HEIGHT / 2;
	gd->time = 0;
	gd->old_time = 0;
	if (init_graphics_has_error(gd))
		return (free(gd->textures), free(gd->tex_rgb), gd->exit_status);
	return (gd->exit_status = EXIT_SUCCESS);
}

static int	init_graphics_has_error(t_gdata *gd)
{
	gd->mlx = mlx_init();
	if (!gd->mlx)
		return (gd->exit_status = EMLXINIT);
	gd->win = mlx_new_window(gd->mlx, W_WIDTH, W_HEIGHT, "cub3D");
	if (!gd->win)
		return (mlx_destroy_display(gd->mlx), gd->exit_status = EMLXWINCREATE);
	gd->canvas.img = mlx_new_image(gd->mlx, W_WIDTH, W_HEIGHT);
	if (!gd->canvas.img)
		return (mlx_destroy_display(gd->mlx),
			mlx_destroy_window(gd->mlx, gd->win),
			gd->exit_status = EMLXWINCREATE);
	gd->canvas.addr = (int *)mlx_get_data_addr(gd->canvas.img, &gd->canvas.bpp,
			&gd->canvas.ll, &gd->canvas.endian);
	gd->canvas.w = W_WIDTH;
	gd->canvas.h = W_HEIGHT;
	return (gd->exit_status = EXIT_SUCCESS);
}
