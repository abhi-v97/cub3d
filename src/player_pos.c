/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:40:45 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:19:00 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_pos	pos_init_to_invalid_pos(void);
static t_pos	pos_set_to(double x, double y);

t_pos	player_get_pos_from_map(t_gdata *gdata)
{
	char	**map;
	char	c;
	int		row;
	int		col;

	map = gdata->map;
	row = -1;
	while (++row < gdata->map_height)
	{
		col = -1;
		while (++col < gdata->map_width)
		{
			c = map[row][col];
			if (c != '\0' && ft_strchr("NSEW", c))
				return (pos_set_to(0.5 + col, 0.5 + row));
		}
	}
	return (pos_init_to_invalid_pos());
}

static t_pos	pos_init_to_invalid_pos(void)
{
	t_pos	pos;

	pos.x = -1;
	pos.y = -1;
	return (pos);
}

static t_pos	pos_set_to(double x, double y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

// function to check if player is placed outside map, for whatever reason
// if the player is adjacent to a space, it has to be out of bounds
int	player_outside_map(t_gdata *data, t_pos pos)
{
	int		row;
	int		col;

	col = (int)pos.x;
	row = (int)pos.y;
	if (!data->map || row >= data->map_height
		|| col >= data->map_width || !data->map[row][col])
		return (1);
	if (col > 0 && data->map[row][col - 1] == ' ')
		return (1);
	if (col > 0 && data->map[row - 1][col] == ' ')
		return (1);
	if (data->map[row + 1] && data->map[row + 1][col] == ' ')
		return (1);
	if (data->map[row][col + 1] && data->map[row][col + 1] == ' ')
		return (1);
	return (0);
}

t_ipos	pos_dtoi(t_pos dpos)
{
	return ((t_ipos){(int)dpos.x, (int)dpos.y});
}
