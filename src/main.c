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

#include "cub3d.h"

static void		print_map_info(t_gdata *data);
void	free_data(t_gdata *data);

int	rendering_function(void *param)
{
	const t_gdata *const gd = param;

	usleep(100000);
	int *data = (int *)gd->cnvs.addr;
	int i = 0;
	while (i < (int)(gd->cnvs.w * gd->cnvs.h))
		data[i++] = 0x00c8c8c8;
	// printf("Line %d\n", __LINE__);
	mlx_put_image_to_window(gd->mlx, gd->win, gd->cnvs.img, 0, 0);
	// printf("Line %d\n", __LINE__);
	return (1);
}

int	key_handler(int key, t_gdata *gdata)
{
	(void) gdata;

	if (key == k_ESC)
		mlx_loop_end(gdata->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	(void) argc;
	(void) argv;
	if (argc > 1 && check_arg(argv[1])) // change this later to only accept 1 arg
		exit(1);

	// printf("player pos now: %f\n", gdata.player.pos.x);
	printf("This is the amazing cub3D!\n");
	if (!init_graphics(&gdata))
		return (1);
	parse_file(&gdata, argv[1]);
	check_map(&gdata);
	print_map_info(&gdata);
	gdata.player.pos = player_get_pos_from_map(&gdata);
	// t_pos	p = player_get_pos_from_map(&gdata);
	if (gdata.player.pos.x > 0 && gdata.player.pos.y > 0 && player_outside_map(&gdata, gdata.player.pos))
		return (ft_error("Player out of bounds!"), 1);
	printf("Player X = %f, Y = %f\n", gdata.player.pos.x, gdata.player.pos.y);
	// TODO: remove exit before merging
	free_data(&gdata);
	exit(0);
	mlx_key_hook(gdata.win, key_handler, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, rendering_function, &gdata);
	mlx_loop(gdata.mlx);
	return (0);
}

// prints map info from t_gdata struct
static void	print_map_info(t_gdata *data)
{
	int		i;

	printf("map_height:\t\t%i\n", data->map_height);
	printf("map_width:\t\t%i\n", data->map_width);
	printf("\nTexture info:\n");
	printf("north:\t\t%s\n", data->texture->north);
	printf("south:\t\t%s\n", data->texture->south);
	printf("west:\t\t%s\n", data->texture->west);
	printf("east:\t\t%s\n", data->texture->east);
	printf("floor:\t\t%s\n", data->texture->floor);
	printf("ceil:\t\t%s\n", data->texture->ceiling);
	printf("\nMap:\n");
	i = 0;
	while (data->map[i])
		printf("\t%s\n", data->map[i++]);
}

void	free_data(t_gdata *data)
{
	int		i;

	close_fd(&data->file_fd);
	if (data->texture->north)
		free(data->texture->north);
	if (data->texture->west)
		free(data->texture->west);
	if (data->texture->south)
		free(data->texture->south);
	if (data->texture->east)
		free(data->texture->east);
	if (data->texture->floor)
		free(data->texture->floor);
	if (data->texture->ceiling)
		free(data->texture->ceiling);
	i = 0;
	while (data->map && data->map[i])
		free(data->map[i++]);
	free(data->map);
	if (data->mlx)
	{
		mlx_destroy_image(data->mlx, data->cnvs.img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data->texture);
}
