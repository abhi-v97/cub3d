/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/26 16:20:10 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <linux/limits.h>

static void		print_map_info(t_gdata *data);

int	rendering_function(void *param)
{
	const t_gdata *const gd = param;

	usleep(100000);
	int *data = (int *)gd->cnvs.addr;
	int i = 0;
	while (i < (int)(gd->cnvs.w * gd->cnvs.h))
		data[i++] = 0x00c8c8c8;
	i = -1;
	while (++i < 256 * 256)
		data[i] = gd->test->address[i];
	// printf("Line %d\n", __LINE__);
	mlx_put_image_to_window(gd->mlx, gd->win, gd->cnvs.img, 0, 0);
	// printf("Line %d\n", __LINE__);
	
	return (1);
}

void	init_img(t_img *img)
{
	img->img = NULL;
	img->address = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

int *parse_xpm(t_gdata *data, char *path)
{
	t_img	*img;
	int		*buffer;
	// int		i;
	// int		j;

	img = (t_img *) malloc(sizeof(t_img *));
	init_img(img);
	buffer = NULL;
	img->img = mlx_xpm_file_to_image(data->mlx, path, &data->texture_path->size, &data->texture_path->size);
	if (img->img == NULL)
		exit(1);
	img->address = (int *)mlx_get_data_addr(img->img, &img->pixel_bits, &img->size_line, &img->endian);
	data->test = img;
	return (buffer);
}

void	load_textures(t_gdata *data)
{
	data->texture = (int **) malloc(sizeof(int *) * 7);
	if (!data->texture)
		exit(1);
	data->texture[7] = 0;
	data->texture[NORTH] = parse_xpm(data, data->texture_path->north);
}

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (argc < 2)
		return (printf("need a map!\n"), 1);
	if (check_arg(argv[1]))
		exit(1);
	printf("This is the amazing cub3D!\n");
	init_gdata(&gdata);
	parse_file(&gdata, argv[1]);
	check_map(&gdata);
	print_map_info(&gdata);
	gdata.player.pos = player_get_pos_from_map(&gdata);
	// t_pos	p = player_get_pos_from_map(&gdata);
	if (gdata.player.pos.x > 0 && gdata.player.pos.y > 0 && player_outside_map(&gdata, gdata.player.pos))
		return (ft_error("Player out of bounds!"), 1);
	printf("Player X = %f, Y = %f\n", gdata.player.pos.x, gdata.player.pos.y);
	
	load_textures(&gdata);

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
	printf("north:\t\t%s\n", data->texture_path->north);
	printf("south:\t\t%s\n", data->texture_path->south);
	printf("west:\t\t%s\n", data->texture_path->west);
	printf("east:\t\t%s\n", data->texture_path->east);
	printf("floor:\t\t%s\n", data->texture_path->floor);
	printf("ceil:\t\t%s\n", data->texture_path->ceiling);
	printf("\nMap:\n");
	i = 0;
	while (data->map[i])
		printf("\t%s\n", data->map[i++]);
}
