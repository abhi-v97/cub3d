/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:33:14 by abhi              #+#    #+#             */
/*   Updated: 2025/07/09 23:03:18 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_horizontal_border(char *map);
static bool	check_vertical_border(char **map, int map_height);
static bool	check_map_validity(t_gdata *gd, char **map);

int	check_map(t_gdata *gd)
{
	if (!gd->map || failed(check_horizontal_border(gd->map[0]))
		|| failed(check_horizontal_border(gd->map[gd->map_height - 1])))
		return (ft_error("Map has incorrect horizontal borders!"),
			exit_status(gd, EMAPHBORDER));
	if (failed(check_vertical_border(gd->map, gd->map_height)))
		return (ft_error("Map has incorrect vertical borders!"),
			exit_status(gd, EMAPVBORDER));
	if (check_map_validity(gd, gd->map))
		return (gd->exit_status);
	if (failed(check_map_bounds(gd, gd->map, gd->map_height)))
		return (gd->exit_status);
	return (exit_status(gd, EXIT_SUCCESS));
}

// checks the horizontal lines (north and south) 
// returns true if it only contains spaces or 1
static bool	check_horizontal_border(char *map)
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
static bool	check_vertical_border(char **map, int map_height)
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

static bool	check_map_validity(t_gdata *gd, char **map)
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
			if (map[row][col] && ft_strchr("NSEW", map[row][col]))
			{
				if (player_found)
					return (exit_status(gd, E_INV_PLAYER), true);
				player_found = true;
			}
			else if (!ft_strchr("01NSWED ", map[row][col]))
				return (exit_status(gd, EMAPINVCHAR), true);
		}
	}
	if (player_found)
		return (exit_status(gd, EXIT_SUCCESS), false);
	return (exit_status(gd, E_INV_PLAYER), true);
}
