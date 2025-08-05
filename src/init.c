/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/08/05 19:04:22 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	alloc_textures(t_gdata *gd);

int	init_map_data(t_gdata *gd)
{
	gd->map = NULL;
	gd->map_height = 0;
	gd->map_width = 0;
	gd->player.pos.x = 0.0;
	gd->player.pos.y = 0.0;
	memset(gd->keys, 0, KEY_COUNT * sizeof(int));
	gd->time = get_time_stamp();
	gd->old_time = 0;
	gd->file_fd = -1;
	gd->weapon_frame = 0;
	gd->weapon_state = 0;
	gd->current_weapon = 0;
	gd->weapon_auto = 0;
	gd->pitch = 0;
	if (failed(alloc_textures(gd)))
		return (gd->exit_status);
	gd->mlx = mlx_init();
	if (!gd->mlx)
		return (exit_status(gd, EMLXINIT));
	return (0);
}

// will free everything, no need for cleanup outside for init_mlx
int	init_mlx(t_gdata *gd)
{
	gd->win = mlx_new_window(gd->mlx, W_WIDTH, W_HEIGHT, "cub3D");
	if (!gd->win)
		return (mlx_destroy_display(gd->mlx), exit_status(gd, EMLXWINCREATE));
	gd->canvas.img = mlx_new_image(gd->mlx, W_WIDTH, W_HEIGHT);
	if (!gd->canvas.img)
		return (mlx_destroy_window(gd->mlx, gd->win),
			mlx_destroy_display(gd->mlx),
			exit_status(gd, EMLXIMGCREATE));
	gd->canvas.addr = (int *)mlx_get_data_addr(gd->canvas.img, &gd->canvas.bpp,
			&gd->canvas.ll, &gd->canvas.endian);
	gd->canvas.w = W_WIDTH;
	gd->canvas.h = W_HEIGHT;
	return (exit_status(gd, EXIT_SUCCESS));
}

// will free everything, no need for cleanup outside for alloc_textures
static int	alloc_textures(t_gdata *gd)
{
	gd->tex_rgb = ft_calloc(sizeof(int), 8);
	if (!gd->tex_rgb)
		return (exit_status(gd, ERR_MALLOC));
	gd->textures = ft_calloc(sizeof(int *), 8);
	gd->weapon = ft_calloc(sizeof(int *), 5);
	if (!gd->textures)
		return (free(gd->tex_rgb), exit_status(gd, ERR_MALLOC));
	return (EXIT_SUCCESS);
}
