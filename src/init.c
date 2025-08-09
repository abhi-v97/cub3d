/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/08/09 17:46:11 by avalsang         ###   ########.fr       */
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
	gd->time = 0;
	gd->old_time = 0;
	gd->file_fd = -1;
	gd->weapon.frame = 0;
	gd->weapon.state = 0;
	gd->weapon.current = 0;
	gd->weapon.auto_fire = 0;
	gd->pitch = 0;
	gd->num_sprite_tex = 0;
	gd->num_sprite_pos = 0;
	gd->win = NULL;
	gd->canvas.img = NULL;
	gd->minimap.colour_array = NULL;
	gd->mlx = mlx_init();
	if (!gd->mlx)
		return (exit_status(gd, EMLXINIT));
	if (failed(alloc_textures(gd)))
		return (gd->exit_status);
	return (0);
}

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

static int	alloc_textures(t_gdata *gd)
{
	gd->tex_rgb = ft_calloc(sizeof(int), 8);
	if (!gd->tex_rgb)
		return (exit_status(gd, ERR_MALLOC));
	gd->textures = ft_calloc(sizeof(int *), 8);
	if (!gd->textures)
		return (free(gd->tex_rgb), exit_status(gd, ERR_MALLOC));
	gd->sprite_tex = ft_calloc(sizeof(int *), 5);
	if (!gd->sprite_tex)
		return (free(gd->tex_rgb), free(gd->textures), exit_status(gd,
				ERR_MALLOC));
	gd->weapon.model = ft_calloc(sizeof(int *), 5);
	if (!gd->weapon.model)
		return (free(gd->tex_rgb), free(gd->textures), free(gd->sprite_tex),
			exit_status(gd, ERR_MALLOC));
	return (EXIT_SUCCESS);
}
