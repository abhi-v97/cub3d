/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025-07-31 21:36:49 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_game_data(t_gdata *gd, int argc, char **argv);
static int	set_start_pos(t_gdata *gd);
static void	player_set_direction(t_gdata *gd);

int	main(int argc, char **argv)
{
	t_gdata		gdata;

	if (failed(init_game_data(&gdata, argc, argv)))
		return (handle_error(gdata.exit_status, argv));
	mlx_hook(gdata.win, KeyPress, KeyPressMask, key_press, &gdata);
	mlx_hook(gdata.win, KeyRelease, KeyReleaseMask, key_release, &gdata);
	mlx_hook(gdata.win, DestroyNotify, NoEventMask, mlx_loop_end, gdata.mlx);
	mlx_loop_hook(gdata.mlx, render_loop, &gdata);
	mlx_loop(gdata.mlx);
	cleanup(&gdata);
	return (EXIT_SUCCESS);
}

static int	init_game_data(t_gdata *gd, int argc, char **argv)
{
	set_program_name(argv[0]);
	if (argc != 2)
		return (exit_status(gd, EINVARGS));
	if (failed(check_arg(gd, argv[1])))
		return (gd->exit_status);
	if (failed(parse_file(gd, argv[1])))
		return (cleanup(gd), gd->exit_status);
	if (failed(check_map(gd)))
		return (cleanup(gd), gd->exit_status);
	set_start_pos(gd);
	player_set_direction(gd);
	if (failed(init_mlx(gd)))
		return (gd->exit_status);
	return (exit_status(gd, EXIT_SUCCESS));
}

static void	player_set_direction(t_gdata *gd)
{
	t_cardinal	cardinal;
	int			player_dir;

	static const
		double direction_consts[][4] = {
	{0, -1, 0.66, 0},
	{0, 1, -0.66, 0},
	{1, 0, 0, 0.66},
	{-1, 0, 0, -0.66}
	};
	player_dir = map_get(gd, gd->player.pos.x, gd->player.pos.y);
	if (player_dir == 'N')
		cardinal = NORTH;
	else if (player_dir == 'S')
		cardinal = SOUTH;
	else if (player_dir == 'E')
		cardinal = EAST;
	else
		cardinal = WEST;
	gd->dir.x = direction_consts[cardinal][DIRX];
	gd->dir.y = direction_consts[cardinal][DIRY];
	gd->plane.x = direction_consts[cardinal][PLANEX];
	gd->plane.y = direction_consts[cardinal][PLANEY];
}

static int	set_start_pos(t_gdata *gd)
{
	char	**map;
	char	c;
	int		row;
	int		col;

	map = gd->map;
	row = -1;
	while (++row < gd->map_height)
	{
		col = -1;
		while (++col < gd->map_width)
		{
			c = map[row][col];
			if (c != '\0' && ft_strchr("NSEW", c))
			{
				gd->player.pos.x = 0.5 + col;
				gd->player.pos.y = 0.5 + row;
				return (0);
			}
		}
	}
	return (1);
}
