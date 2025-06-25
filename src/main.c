/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/25 14:33:11 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		print_map_info(t_gdata *data);

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (argc > 1 && check_arg(argv[1])) // change this later to only accept 1 arg
		exit(1);
	printf("This is the amazing cub3D!\n");
	if (!init_all(&gdata))
		return (cleanup(&gdata), gdata.exit_code);
	parse_file(&gdata, argv[1]);
	check_map(&gdata);
	print_map_info(&gdata);
	t_pos	p = player_get_pos_from_map(&gdata);
	printf("Player X = %f, Y = %f\n", p.x, p.y);
	mlx_key_hook(gdata.win, key_handler, &gdata);
	mlx_hook(gdata.win, 17, 0, mlx_loop_end, gdata.display);
	mlx_loop_hook(gdata.display, render_screen, &gdata);
	mlx_loop(gdata.display);
	return (0);
}

// prints map info from t_gdata struct
static void	print_map_info(t_gdata *data)
{
	int		i;

	printf("map_height:\t%i\n", data->map_height);
	printf("map_width:\t%i\n", data->map_width);
	printf("\nMap:\n");
	i = 0;
	while (data->map[i])
		printf("\t%s\n", data->map[i++]);
}
