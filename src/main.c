/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/30 22:08:28 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <linux/limits.h>	//TO-DO: is this needed?

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (argc < 2)
		return (printf("need a map!\n"), 1);
	if (check_arg(argv[1]))
		return (1);
	printf("This is the amazing cub3D!\n");
	if (init_gdata(&gdata) || parse_file(&gdata, argv[1]))
		return (cleanup(&gdata), 1);
	if (check_map(&gdata))
		return (cleanup(&gdata), 1);
	print_map_info(&gdata);
	gdata.player.pos = player_get_pos_from_map(&gdata); //TO-DO: need to move this to an init function
	player_set_direction(&gdata); //TO-DO: need to move this to an init function
	if (gdata.player.pos.x > 0 && gdata.player.pos.y > 0 && player_outside_map(&gdata, gdata.player.pos))
		return (ft_error("Player out of bounds!"), 1);
	printf("Player X = %f, Y = %f\n", gdata.player.pos.x, gdata.player.pos.y);
	printf("mouse x = %i, y = %i\n", gdata.mpos_at_start.x, gdata.mpos_at_start.y);
	//mlx_mouse_hook(gdata.win, mouse_click_handler, &gdata);
	mlx_hook(gdata.win, 2, 1L<<0, key_press, &gdata);
	mlx_hook(gdata.win, 3, 1L<<1, key_release, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (0);
}
