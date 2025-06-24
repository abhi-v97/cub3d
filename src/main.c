/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/23 18:47:55 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void		print_map_info(t_gdata *data);

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
	print_map_info(&gdata);
	t_pos	p = player_get_pos_from_map(&gdata);
	printf("Player X = %f, Y = %f\n", p.x, p.y);
	// TODO: remove exit before merging
	exit(0);
	mlx_key_hook(gdata.win, key_handler, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.display);
	mlx_loop_hook(gdata.display, rendering_function, &gdata);
	mlx_loop(gdata.display);
	return (0);
}

// prints map info from t_gdata struct
static void	print_map_info(t_gdata *data)
{
	int		i;

	printf("map_height:\t\t%i\n", data->map_height);
	printf("map_width:\t\t%i\n", data->map_width);
	printf("\nTexture info:\n");
	printf("north:\t\t%s\n", data->texture_n);
	printf("south:\t\t%s\n", data->texture_s);
	printf("west:\t\t%s\n", data->texture_w);
	printf("east:\t\t%s\n", data->texture_e);
	printf("floor:\t\t%s\n", data->texture_f);
	printf("ceil:\t\t%s\n", data->texture_c);
	printf("\nMap:\n");
	i = 0;
	while (data->map[i])
		printf("\t%s\n", data->map[i++]);
}
