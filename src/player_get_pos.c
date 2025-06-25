/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_get_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:40:45 by aistok            #+#    #+#             */
/*   Updated: 2025/06/23 16:18:32 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_pos	player_get_pos_from_map(t_gdata *gdata)
{
	char	**map;
	char	c;
	t_pos	pos;
	int		i;
	int		j;

	pos.x = -1;
	pos.y = -1;
	map = gdata->map;
	i = -1;
	while (++i < gdata->map_height)
	{
		j = 0;
		c = map[i][j];
		while (c)
		{
			if (ft_strchr("NSEW", c))
				return (pos.x = (double)i, pos.y = (double)j, pos);
			c = map[i][++j];
		}
	}
	return (ft_error("Player not found!"), pos);
}

// function to check if player is placed outside map, for whatever reason
// if the player is adjacent to a space, it has to be out of bounds
int player_outside_map(t_gdata *data, t_pos pos)
{
	int		x;
	int		y;

	x = (int)pos.x;
	y = (int)pos.y;
	if (!data->map && x > data->map_width && y > data->map_height && !data->map[x][y])
		return (1);
	if (y > 0 && (data->map[x][y - 1] == ' '))
		return (1);
	if (x > 0 && (data->map[x - 1][y] == ' '))
		return (1);
	if (data->map[x + 1] && data->map[x + 1][y] == ' ')
		return (1);
	if (data->map[y + 1] && data->map[x][y + 1] == ' ')
		return (1);
	return (0);
}
