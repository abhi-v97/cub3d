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

static void	set_pos(t_gdata *gd, double x, double y);

int	set_start_pos(t_gdata *gd)
{
	char	**map;
	char	c;
	int		row;
	int		col;

	map = gd->map;
	row = -1;
	while (++row < gd->map_height)
	{
		col = -1;
		while (++col < gd->map_width)
		{
			c = map[row][col];
			if (c != '\0' && ft_strchr("NSEW", c))
				return (set_pos(gd, 0.5 + col, 0.5 + row), 0);
		}
	}
	return (1);
}

static void	set_pos(t_gdata *gd, double x, double y)
{
	gd->player.pos.x = x;
	gd->player.pos.y = y;
}

t_ipos	pos_dtoi(t_pos dpos)
{
	return ((t_ipos){(int)dpos.x, (int)dpos.y});
}
