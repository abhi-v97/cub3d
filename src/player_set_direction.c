/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_set_direction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:55:35 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:18:21 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_set_direction(t_gdata *gd)
{
	t_cardinal	cardinal;

	static const
		double direction_consts[][4] = {
	{-1, 0, 0, 0.66},
	{1, 0, 0, -0.66},
	{0, 1, -0.66, 0},
	{0, -1, 0.66, 0}
	};
	gd->player_direction = map_get(gd, gd->player.pos.x, gd->player.pos.y);
	if (gd->player_direction == 'N')
		cardinal = NORTH;
	else if (gd->player_direction == 'S')
		cardinal = SOUTH;
	else if (gd->player_direction == 'E')
		cardinal = EAST;
	else if (gd->player_direction == 'W')
		cardinal = WEST;
	gd->dir.x = direction_consts[cardinal][DIRX];
	gd->dir.y = direction_consts[cardinal][DIRY];
	gd->plane.x = direction_consts[cardinal][PLANEX];
	gd->plane.y = direction_consts[cardinal][PLANEY];
}
