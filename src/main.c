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

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (failed(check_args_map_and_init(&gdata, argc, argv)))
		return (handle_error(gdata.exit_status, argc, argv));
	mlx_hook(gdata.win, KeyPress, KeyPressMask, key_press, &gdata);
	mlx_hook(gdata.win, KeyRelease, KeyReleaseMask, key_release, &gdata);
	mlx_hook(gdata.win, DestroyNotify, NoEventMask, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (EXIT_SUCCESS);
}
