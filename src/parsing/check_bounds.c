/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bounds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-23 17:29:36 by avalsang          #+#    #+#             */
/*   Updated: 2025-06-23 17:29:36 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_missing_wall(t_gdata *data, char **map, int i, int j);

// checks if map has no empty gaps in walls
// loops through every char until it finds an empty space '-'
// if the empty space isn't surrounded by another '-' or a wall (1),
// it means there is a gap in the wall
int	check_map_bounds(t_gdata *data, char **map, int map_height)
{
	int		i;
	int		j;

	if (!map || !*map)
		return (1);
	i = 0;
	while (i < map_height - 1)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '-' && check_missing_wall(data, map, i, j))
				return (ft_error("missing wall"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

// checks if each empty space is surrounded by a 1 or another empty space
// checks left space only if j > 0
// checks right space only if map[i][j + 1] isn't null
// checks up space only if i > 0
// checks down space only if map[i + 1] isn't null
static int	check_missing_wall(t_gdata *data, char **map, int i, int j)
{
	(void) data;
	if (j > 0 && (map[i][j - 1] != '-' && map[i][j - 1] != '1'))
		return (1);
	if (map[i][j + 1] && (map[i][j + 1] != '-' && map[i][j + 1] != '1'))
		return (1);
	if (i > 0 && (map[i - 1][j] != '-' && map[i - 1][j] != '1'))
		return (1);
	if (map[i + 1] && (map[i + 1][j] != '-' && map[i + 1][j] != '1'))
		return (1);
	return (0);
}
