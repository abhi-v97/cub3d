/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:27:15 by aistok            #+#    #+#             */
/*   Updated: 2025/08/05 18:46:11 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_array(char **array);
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

void	free_array(char **array)
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

void	free_data(t_gdata *data)
{
	close_fd(&data->file_fd);
	if (data->map)
		free_array(data->map);
	cleanup_textures(data);
}

static void	cleanup_textures(t_gdata *gd)
{
	int		i;

	i = 0;
	while (i < 7)
	{
		if (gd->textures[i])
			free(gd->textures[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (gd->sprite_tex[i])
			free(gd->sprite_tex[i]);
		i++;
	}
	free(gd->sprite_tex);
	free(gd->textures);
	free(gd->tex_rgb);
}
