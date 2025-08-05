/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:43:10 by avalsang          #+#    #+#             */
/*   Updated: 2025/08/05 19:05:59 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_game_data(t_gdata *gd, int argc, char **argv);
static int	set_start_pos(t_gdata *gd);
static void	player_set_direction(t_gdata *gd);

void	weapon_fire(t_gdata *gd)
{
	if (gd->weapon_state == 0)
	{
		gd->weapon_state = 1;
		gd->weapon_frame = 1;
		if (gd->current_weapon == 0 || gd->current_weapon == 3)
			gd->weapon_auto = 1;
	}
}

int	mouse_events(int button, int x, int y, t_gdata *gd)
{
	// printf("i: %i %i %i %i\n", button, x, y, x);
	(void) x;
	(void) y;
	if (button == 1) // left click
		weapon_fire(gd);
	return (0);
}

int	mouse_release(int button, int x, int y, t_gdata *gd)
{
	(void) x;
	(void) y;
	if (button == 1)
		gd->weapon_auto = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_gdata		gd;

	if (failed(init_game_data(&gd, argc, argv)))
		return (gd.exit_status);
	gd.minimap.colour_array = minimap_colours(&gd);
	set_weapon(&gd);
	find_doors(&gd);
	mlx_hook(gd.win, KeyPress, KeyPressMask, key_press, &gd);
	mlx_hook(gd.win, KeyRelease, KeyReleaseMask, key_release, &gd);
	mlx_hook(gd.win, DestroyNotify, NoEventMask, mlx_loop_end, gd.mlx);
	mlx_hook(gd.win, 4, 1L << 2, mouse_events, &gd);
	mlx_hook(gd.win, 5, 1L << 3, mouse_release, &gd);
	mlx_mouse_move(gd.mlx, gd.win, W_WIDTH / 2, W_HEIGHT / 2);
	mlx_mouse_hide(gd.mlx, gd.win);
	// mlx_hook(gdata.win,  06, 1L << 6,mouse_move, &gdata);
	mlx_loop_hook(gd.mlx, render_loop, &gd);
	mlx_loop(gd.mlx);
	cleanup(&gd);
	return (EXIT_SUCCESS);
}

// is player_outside_map unneccessary? I was not able to make a map that 
// triggers that line of code, a previous error check flags it first
static int	init_game_data(t_gdata *gd, int argc, char **argv)
{
	set_program_name(argv[0]);
	if (argc != 2)
		return (exit_status(gd, EINVARGS));
	if (failed(check_arg(gd, argv[1])))
		return (gd->exit_status);
	if (failed(init_map_data(gd)))
		return (gd->exit_status);
	if (failed(parse_file(gd, argv[1])))
		return (gd->exit_status);
	if (failed(check_map(gd)))
		return (cleanup(gd), exit_status(gd, 1));
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
