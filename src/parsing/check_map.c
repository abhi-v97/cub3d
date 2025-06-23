/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-22 13:33:14 by abhi              #+#    #+#             */
/*   Updated: 2025-06-22 13:33:14 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	check_horizontal(char *map);
static int	check_vertical(char **map, int map_height);
static int	check_invalid_char(t_gdata *data, char **map, int map_height);
static int	check_missing_wall(t_gdata *data, char **map, int i, int j);
static int	check_map_bounds(t_gdata *data, char **map, int map_height);

int	check_map(t_gdata *data)
{
	if (!data->map || check_horizontal(data->map[0])
		|| check_horizontal(data->map[data->map_height - 1]))
		return (ft_error("map has incorrect horizontal borders"), 1);
	if (check_vertical(data->map, data->map_height))
		return (ft_error("map has incorrect vertical borders"), 1);
	if (check_invalid_char(data, data->map, data->map_height))
		return (1);
	if (check_map_bounds(data, data->map, data->map_height))
		return (1);
	printf("Map borders OKAY\n");
	return (0);
}

// checks the horizontal lines (north and south) 
// returns true if it only contains spaces or 1
static int	check_horizontal(char *map)
{
	int		i;

	i = 0;
	if (!map || !map[i])
		return (1);
	while (map[i])
	{
		if (is_blank(map[i]))
			;
		else if (map[i] != '1' && map[i] != '-')
			return (1);
		i++;
	}
	return (0);
}

// checks every line, except first and last, if its demarcated by 1
// skips over blank space at the start and end
static int	check_vertical(char **map, int map_height)
{
	int		i;
	int		j;

	i = 1;
	while (i < map_height - 1)
	{
		j = 0;
		while (map[i][j] == '-')
			j++;
		if (map[i][j] != '1')
			return (1);
		j = ft_strlen(map[i]) - 1;
		while (map[i][j] == '-')
			j--;
		if (map[i][j] != '1')
			return (1);
		i++;
	}
	return (0);
}

static int	check_invalid_char(t_gdata *data, char **map, int map_height)
{
	int		i;
	int		j;

	if (!map || !*map)
		return (1);
	i = 1;
	while (i < map_height - 1)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '-')
				;
			else if (!ft_strchr("01NSWE", map[i][j]))
				return (ft_error("invalid character found"), 1);
			else if (ft_strchr("NSWE", map[i][j]) && data->player_direction == 0)
				data->player_direction = map[i][j];
			else if (ft_strchr("NSWE", map[i][j]) && data->player_direction != 0)
				return (ft_error("too many players"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_map_bounds(t_gdata *data, char **map, int map_height)
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

// checks if the map has a missing wall that would cause
// players to fall out of the map
static int	check_missing_wall(t_gdata *data, char **map, int i, int j)
{
	(void) data;
	if (j > 0 && (map[i][j - 1] != '-' && map[i][j - 1] != '1'))
		return (1);
	if (map[i][j + 1] && (map[i][j + 1] != '-' && map[i][j + 1] != '1'))
		return (1);
	if (i > 1 && (map[i - 1][j] != '-' && map[i - 1][j] != '1'))
		return (1);
	if (map[i + 1] && (map[i + 1][j] != '-' && map[i + 1][j] != '1'))
		return (1);
	return (0);
}
