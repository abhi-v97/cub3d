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

void    cleanup(t_gdata *gdata)
{
	if (gdata->cnvs.img)
		mlx_destroy_image(gdata->mlx, gdata->cnvs.img);
	if (gdata->win)
		mlx_destroy_window(gdata->mlx, gdata->win);
	if (gdata->mlx)
	{
		mlx_destroy_display(gdata->mlx);
		free(gdata->mlx);
	}
	free_data(gdata);
}


static void	free_data(t_gdata *data)
{
	int		i;

	close_fd(&data->file_fd);
	if (data->texture_path->north)
		free(data->texture_path->north);
	if (data->texture_path->west)
		free(data->texture_path->west);
	if (data->texture_path->south)
		free(data->texture_path->south);
	if (data->texture_path->east)
		free(data->texture_path->east);
	if (data->texture_path->floor)
		free(data->texture_path->floor);
	if (data->texture_path->ceiling)
		free(data->texture_path->ceiling);
	i = 0;
	while (data->map && data->map[i])
		free(data->map[i++]);
	free(data->map);
	free(data->texture_path);
}
