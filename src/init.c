/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:34:09 by aistok            #+#    #+#             */
/*   Updated: 2025/07/10 07:24:41 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_gdata(t_gdata *gd);
static int	alloc_textures(t_gdata *gd);
static void	free_textures(t_gdata *gd);
static int	init_mlx(t_gdata *gd);

int	init_all(t_gdata *gd)
{
	init_gdata(gd);
	if (failed(alloc_textures(gd)))
		return (gd->exit_status);
	if (failed(init_mlx(gd)))
		return (free_textures(gd), gd->exit_status);
	return (EXIT_SUCCESS);
}

static void	init_gdata(t_gdata *gd)
{
	gd->map = NULL;
	gd->map_height = 0;
	gd->map_width = 0;
	gd->player.pos.x = 0.0;
	gd->player.pos.y = 0.0;
	gd->player_direction = 0;
	memset(gd->keys, 0, KEY_COUNT * sizeof(int));
	gd->win_center.x = W_WIDTH / 2;
	gd->win_center.y = W_HEIGHT / 2;
	gd->time = 0;
	gd->old_time = 0;
	gd->file_fd = -1;
}

// will free everything, no need for cleanup outside for alloc_textures
static int	alloc_textures(t_gdata *gd)
{
	gd->tex_rgb = ft_calloc(sizeof(int), 7);
	if (!gd->tex_rgb)
		return (exit_status(gd, ENOMEM));
	gd->textures = ft_calloc(sizeof(int *), 7);
	if (!gd->textures)
		return (free(gd->tex_rgb), exit_status(gd, ENOMEM));
	return (EXIT_SUCCESS);
}

static void	free_textures(t_gdata *gd)
{
	free(gd->textures);
	free(gd->tex_rgb);
}

// will free everything, no need for cleanup outside for init_mlx
static int	init_mlx(t_gdata *gd)
{
	gd->mlx = mlx_init();
	if (!gd->mlx)
		return (exit_status(gd, EMLXINIT));
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
