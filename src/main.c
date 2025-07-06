/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/07/06 12:24:59 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (check_error_in_args_map_or_init(&gdata, argc, argv))
		return (gdata.exit_status);
	mlx_hook(gdata.win, 2, 1L<<0, key_press, &gdata);
	mlx_hook(gdata.win, 3, 1L<<1, key_release, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (0);
}
