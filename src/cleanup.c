/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:27:15 by aistok            #+#    #+#             */
/*   Updated: 2025/06/26 13:16:45 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_data(t_gdata *data);

void	cleanup(t_gdata *gdata)
{
	if (gdata->cnvs.img)
		mlx_destroy_image(gdata->mlx, gdata->cnvs.img);
	if (gdata->win)
		mlx_destroy_window(gdata->mlx, gdata->win);
	if (gdata->mlx)
	{
		mlx_destroy_display(gdata->mlx);
		mlx_loop_end(gdata->mlx);
		free(gdata->mlx);
	}
	free_data(gdata);
}

void	free_array(char **array)
{
	int		i;
	
	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
}

static void	free_data(t_gdata *data)
{
	int		i;

	close_fd(&data->file_fd);
	i = 0;
	while (i < 7)
	{
		if (data->textures[i])
			free(data->textures[i]);
		i++;
	}
	if (data->map)
		free_array(data->map);
	free(data->textures);
	free(data->tex_rgb);
}
