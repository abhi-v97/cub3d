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

int	mouse_events(int button, int x, int y, t_gdata *gd)
{
	printf("i: %i %i %i %i\n", button, x, y, x);
	if (button == 1) // left click
		gd->weapon_frame++;
	return (0);
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
	mlx_mouse_hook(gdata.win, mouse_events, &gdata);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (EXIT_SUCCESS);
}
