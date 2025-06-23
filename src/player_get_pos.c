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

#include "../inc/cub3d.h"

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
	return (pos);
}
