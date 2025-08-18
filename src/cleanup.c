/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:27:15 by aistok            #+#    #+#             */
/*   Updated: 2025/07/13 20:58:12 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_textures(t_gdata *gd);

void	cleanup(t_gdata *gd)
{
	if (gd->canvas.img)
		mlx_destroy_image(gd->mlx, gd->canvas.img);
	if (gd->win)
		mlx_destroy_window(gd->mlx, gd->win);
	if (gd->mlx)
	{
		mlx_destroy_display(gd->mlx);
		mlx_loop_end(gd->mlx);
		free(gd->mlx);
	}
	free_data(gd);
}

void	free_array(void **array)
{
	int		i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_data(t_gdata *gd)
{
	close_fd(&gd->file_fd);
	if (gd->map)
		free_array((void **)gd->map);
	cleanup_textures(gd);
}

static void	cleanup_textures(t_gdata *gd)
{
	int		i;

	i = 0;
	if (gd->textures)
	{
		while (i < 7)
		{
			if (gd->textures[i])
				free(gd->textures[i]);
			i++;
		}
		free(gd->textures);
	}
	if (gd->tex_rgb)
		free(gd->tex_rgb);
}
