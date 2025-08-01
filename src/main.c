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

void	weapon_fire(t_gdata *gd)
{
	if (gd->weapon_state == 0)
	{
		gd->weapon_state = 1;
		gd->weapon_frame = 1;
		if (gd->current_weapon == 0 || gd->current_weapon == 3)
			gd->weapon_auto = 1;
	}
}

int	mouse_events(int button, int x, int y, t_gdata *gd)
{
	// printf("i: %i %i %i %i\n", button, x, y, x);
	(void) x;
	(void) y;
	if (button == 1) // left click
		weapon_fire(gd);
	return (0);
}

int	mouse_release(int button, int x, int y, t_gdata *gd)
{
	(void) x;
	(void) y;
	if (button == 1)
		gd->weapon_auto = 0;
	return (0);
}

// int	mouse_move(int x, int y, t_gdata *gd)
// {
// 	(void) gd;
// 	(void) x;
// 	(void) y;
// 	mlx_mouse_move(gd->mlx, gd->win, W_WIDTH / 2, W_HEIGHT / 2);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (failed(check_args_map_and_init(&gdata, argc, argv)))
		return (gdata.exit_status);
	gdata.minimap.colour_array = minimap_colours(&gdata);
	set_weapon(&gdata);
	find_doors(&gdata);
	mlx_hook(gdata.win, KeyPress, KeyPressMask, key_press, &gdata);
	mlx_hook(gdata.win, KeyRelease, KeyReleaseMask, key_release, &gdata);
	mlx_hook(gdata.win, DestroyNotify, NoEventMask, mlx_loop_end, gdata.mlx);
	mlx_hook(gdata.win, 4, 1L << 2, mouse_events, &gdata);
	mlx_hook(gdata.win, 5, 1L << 3, mouse_release, &gdata);
	mlx_mouse_move(gdata.mlx, gdata.win, W_WIDTH / 2, W_HEIGHT / 2);
	mlx_mouse_hide(gdata.mlx, gdata.win);
	// mlx_hook(gdata.win,  06, 1L << 6,mouse_move, &gdata);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (EXIT_SUCCESS);
}
