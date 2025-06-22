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
static int	check_invalid_char(char **map, int map_height);

int	check_map(t_gdata *data)
{
	if (!data->map || check_horizontal(data->map[0])
		|| check_horizontal(data->map[data->map_height - 1]))
		return (ft_error("map has incorrect horizontal borders"), 1);
	if (check_vertical(data->map, data->map_height))
		return (ft_error("map has incorrect vertical borders"), 1);
	if (check_invalid_char(data->map, data->map_height))
		return (ft_error("map has invalid characters"), 1);
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
		else if (map[i] != '1')
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
		while (is_blank(map[i][j]))
			j++;
		if (map[i][j] != '1')
			return (1);
		j = ft_strlen(map[i]) - 2;
		while (is_blank(map[i][j]))
			j--;
		if (map[i][j] != '1')
			return (1);
		i++;
	}
	return (0);
}

static int	check_invalid_char(char **map, int map_height)
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
			if (is_blank(map[i][j]))
				;
			else if (!ft_strchr("01NSEW", map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
