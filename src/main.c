/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/07/13 21:39:36 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_doors(t_gdata *gd)
{
	int		row;
	int		col;
	int		i;

	row = -1;
	i = 0;
	while (++row < gd->map_height)
	{
		col = -1;
		while (++col < gd->map_width)
		{
			if (gd->map[row][col] == 'D')
			{
				gd->door[i].x = col;		
				gd->door[i++].y = row;		
			}
		}
	}
	gd->num_doors = i;
}

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (failed(check_args_map_and_init(&gdata, argc, argv)))
		return (gdata.exit_status);
	gdata.minimap.colour_array = minimap_colours(&gdata);
	find_doors(&gdata);
	mlx_hook(gdata.win, KeyPress, KeyPressMask, key_press, &gdata);
	mlx_hook(gdata.win, KeyRelease, KeyReleaseMask, key_release, &gdata);
	mlx_hook(gdata.win, DestroyNotify, NoEventMask, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (EXIT_SUCCESS);
}
