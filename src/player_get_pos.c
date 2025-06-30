/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_get_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:40:45 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 17:58:29 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	pos_nsew_to_angle(char c);
t_pos	pos_init_to_invalid_pos(void);
t_pos	pos_set_to(double x, double y);

t_pos	player_get_pos_from_map(t_gdata *gdata)
{
	char	**map;
	char	c;
	int		i;
	int		j;

	map = gdata->map;
	i = -1;
	while (++i < gdata->map_height)
	{
		j = 0;
		c = map[i][j];
		while (c)
		{
			if (ft_strchr("NSEW", c))
				return (pos_set_to((double)j, (double)i));
			c = map[i][++j];
		}
	}
	return (pos_init_to_invalid_pos());
}

double	pos_nsew_to_angle(char c)
{
	if (c == 'N')
		return (0);
	else if (c == 'E')
		return (90);
	else if (c == 'S')
		return (180);
	else if (c == 'W')
		return (270);
	return (-1);
}

t_pos	pos_init_to_invalid_pos(void)
{
	t_pos	pos;

	pos.x = -1;
	pos.y = -1;
	return (pos);
}

t_pos	pos_set_to(double x, double y)
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
	int		i;
	int		j;

	i = (int)pos.y;
	j = (int)pos.x;
	if (!data->map && i > data->map_width && j > data->map_height && !data->map[i][j])
		return (1);
	if (j > 0 && data->map[i][j - 1] == ' ')
		return (1);
	if (i > 0 && data->map[i - 1][j] == ' ')
		return (1);
	if (data->map[i + 1] && data->map[i + 1][j] == ' ')
		return (1);
	if (data->map[i][j + 1] && data->map[i][j + 1] == ' ')
		return (1);
	return (0);
}
