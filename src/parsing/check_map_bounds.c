/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:29:36 by avalsang          #+#    #+#             */
/*   Updated: 2025/07/09 23:03:27 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_missing_wall(t_gdata *gd, char **map, int row, int col);
static bool	is_space_or_wall(char c);

// checks if map has no empty gaps in walls
// loops through every char until it finds an empty space ' '
// if the empty space isn't surrounded by another ' ' or a wall (1),
// it means there is a gap in the wall
int	check_map_bounds(t_gdata *gd, char **map, int map_height)
{
	int		row;
	int		col;

	if (!map || !*map)
		return (1);
	row = 0;
	while (row < map_height - 1)
	{
		col = 0;
		while (map[row][col])
		{
			if (map[row][col] == ' ' && check_missing_wall(gd, map, row, col))
				return (ft_error("Missing wall!"),
					exit_status(gd, EMAPWALLMISSING));
			col++;
		}
		row++;
	}
	return (exit_status(gd, EXIT_SUCCESS));
}

// checks if each empty space is surrounded by a 1 or another empty space
// checks left space only if j > 0
// checks right space only if map[i][j + 1] isn't null
// checks up space only if i > 0
// checks down space only if map[i + 1] isn't null
static bool	check_missing_wall(t_gdata *gd, char **map, int row, int col)
{
	if (col > 0 && is_space_or_wall(map[row][col - 1]))
		return (true);
	if (col + 1 < gd->map_width
		&& is_space_or_wall(map[row][col + 1]))
		return (true);
	if (row > 0 && is_space_or_wall(map[row - 1][col]))
		return (true);
	if (row + 1 < gd->map_height
		&& is_space_or_wall(map[row + 1][col]))
		return (true);
	return (false);
}

static bool	is_space_or_wall(char c)
{
	if (!c)
		return (false);
	return (!(c == ' ' || c == '1'));
}
