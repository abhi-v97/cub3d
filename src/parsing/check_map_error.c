/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:33:14 by abhi              #+#    #+#             */
/*   Updated: 2025/07/07 23:39:33 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_horizontal_border_missing(char *map);
static bool	check_vertical_border_missing(char **map, int map_height);
static int	check_invalid_char(t_gdata *data, char **map, int map_height);
static bool	check_only_one_player(t_gdata *gd, char **map);

int	check_map_error(t_gdata *gd)
{
	if (!gd->map || check_horizontal_border_missing(gd->map[0])
		|| check_horizontal_border_missing(gd->map[gd->map_height - 1]))
		return (ft_error("Map has incorrect horizontal borders"),
			exit_status(gd, EMAPHBORDERERR));
	if (check_vertical_border_missing(gd->map, gd->map_height))
		return (ft_error("Map has incorrect vertical borders"),
			exit_status(gd, EMAPVBORDERERR));
	if (check_invalid_char(gd, gd->map, gd->map_height))
		return (gd->exit_status);
	if (!check_only_one_player(gd, gd->map))
		return (ft_error("singleplayer only!"), gd->exit_status);
	if (check_map_bounds_missing(gd, gd->map, gd->map_height))
		return (gd->exit_status);
	return (exit_status(gd, EXIT_SUCCESS));
}

// checks the horizontal lines (north and south) 
// returns true if it only contains spaces or 1
static bool	check_horizontal_border_missing(char *map)
{
	int		row;

	row = 0;
	if (!map || !map[row])
		return (true);
	while (map[row])
	{
		if (map[row] != '1' && map[row] != ' ')
			return (true);
		row++;
	}
	return (false);
}

// checks every line, except first and last, if its demarcated by 1
// skips over blank space at the start and end
static bool	check_vertical_border_missing(char **map, int map_height)
{
	int		row;
	int		col;

	row = 1;
	while (row < map_height - 1)
	{
		col = 0;
		while (map[row][col] == ' ')
			col++;
		if (map[row][col] != '1')
			return (true);
		col = ft_strlen(map[row]) - 1;
		while (map[row][col] == ' ')
			col--;
		if (map[row][col] != '1')
			return (true);
		row++;
	}
	return (false);
}

// checks if map has any invalid characters
// allowed chars: 01NSWE and ' ' (empty space)
static int	check_invalid_char(t_gdata *gd, char **map, int map_height)
{
	int		row;
	int		col;

	if (!map || !*map)
		return (exit_status(gd, EMAPEMPTY));
	row = 1;
	while (row < map_height - 1)
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == ' ')
				;
			else if (!ft_strchr("01NSWE", map[row][col]))
				return (ft_error("Invalid character found"),
					exit_status(gd, EMAPINVCHAR));
			col++;
		}
		row++;
	}
	return (exit_status(gd, EXIT_SUCCESS));
}

static bool	check_only_one_player(t_gdata *gd, char **map)
{
	bool	player_found;
	int		row;
	int		col;

	row = -1;
	player_found = false;
	while (++row < gd->map_height)
	{
		col = -1;
		while (++col < gd->map_width)
		{
			if (ft_strchr("NSEW", map[row][col]))
			{
				if (!player_found)
					player_found = true;
				else
					return (exit_status(gd, EMAPTOOMANYPLAYERS), false);
			}
		}
	}
	if (player_found)
		return (exit_status(gd, EXIT_SUCCESS), true);
	return (exit_status(gd, EMAPNOPLAYERS), false);
}
