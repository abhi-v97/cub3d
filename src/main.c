/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/20 19:01:05 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	rendering_function(void *param)
{
	const t_gdata *const gd = param;

	usleep(100000);
	int *data = (int *)gd->cnvs.addr;
	int i = 0;
	while (i < (int)(gd->cnvs.w * gd->cnvs.h))
		data[i++] = 0x00c8c8c8;
	// printf("Line %d\n", __LINE__);
	mlx_put_image_to_window(gd->display, gd->win, gd->cnvs.img, 0, 0);
	// printf("Line %d\n", __LINE__);
	return (1);
}

int	key_handler(int key, t_gdata *gdata)
{
	(void) gdata;

	if (key == k_ESC)
		mlx_loop_end(gdata->display);
	return (1);
}

bool	init_graphics(t_gdata *gdata)
{
	gdata->map = NULL;
	gdata->map_height = 0;

	gdata->ww = 1600;
	gdata->wh = 900;
	gdata->display = mlx_init();
	if (!gdata->display)
		return (false);
	gdata->win = mlx_new_window(gdata->display, gdata->ww, gdata->wh, "cub3D");
	if (!gdata->win)
		return (false);
	gdata->cnvs.img = mlx_new_image(gdata->display, gdata->ww, gdata->wh);
	gdata->cnvs.addr = mlx_get_data_addr(gdata->cnvs.img, &gdata->cnvs.bpp, \
		&gdata->cnvs.ll, &gdata->cnvs.endian);
	gdata->cnvs.w = gdata->ww;
	gdata->cnvs.h = gdata->wh;
	return (true);
}

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	(void) argc;
	(void) argv;
	if (argc > 1 && check_arg(argv[1])) // change this later to only accept 1 arg
		exit(1);

	printf("This is the amazing cub3D!\n");
	if (!init_graphics(&gdata))
		return (1);
	parse_file(&gdata, argv[1]);
	check_map(&gdata);
	// TODO: remove exit before merging
	exit(0);
	mlx_key_hook(gdata.win, key_handler, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.display);
	mlx_loop_hook(gdata.display, rendering_function, &gdata);
	mlx_loop(gdata.display);
	return (0);
}
