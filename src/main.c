/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/30 17:11:09 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <linux/limits.h>

static int	rendering_function(void *param);

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (argc < 2)
		return (printf("need a map!\n"), 1);
	if (check_arg(argv[1]))
		exit(1);
	printf("This is the amazing cub3D!\n");
	init_gdata(&gdata);
	if (parse_file(&gdata, argv[1]))
		(cleanup(&gdata), exit(1)); // double check this, make sure mem is freed correctly
	check_map(&gdata);
	print_map_info(&gdata);
	gdata.player.pos = player_get_pos_from_map(&gdata);
	// t_pos	p = player_get_pos_from_map(&gdata);
	if (gdata.player.pos.x > 0 && gdata.player.pos.y > 0 && player_outside_map(&gdata, gdata.player.pos))
		return (ft_error("Player out of bounds!"), 1);
	printf("Player X = %f, Y = %f\n", gdata.player.pos.x, gdata.player.pos.y);
	mlx_hook(gdata.win, 2, 1L<<0, key_press, &gdata);
	mlx_hook(gdata.win, 3, 1L<<1, key_release, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (0);
}

static int	rendering_function(void *param)
{
	t_gdata *gd = param;

	usleep(100000);
	int *data = (int *)gd->cnvs.addr;
	int i = 0;
	while (i < (int)(gd->cnvs.w * gd->cnvs.h))
		data[i++] = 0x00c8c8c8;

	// dummy code used to test textures
	test_textures(gd, gd->textures[NORTH], 100);
	test_textures(gd, gd->textures[WEST], 400);
	test_textures(gd, gd->textures[SOUTH], 700);
	test_textures(gd, gd->textures[EAST], 1000);

	mlx_put_image_to_window(gd->mlx, gd->win, gd->cnvs.img, 0, 0);
	
	return (1);
}
