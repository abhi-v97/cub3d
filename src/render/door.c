/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-22 15:18:55 by abhi              #+#    #+#             */
/*   Updated: 2025-07-22 15:18:55 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	find_doors(t_gdata *gd)
{
	int		row;
	int		col;
	int		i;

	row = -1;
	i = 0;
	while (++row < gd->map_height)
	{
		col = -1;
		while (++col < gd->map_width)
		{
			if (gd->map[row][col] == 'D')
			{
				gd->door[i].x = col;
				gd->door[i++].y = row;
			}
		}
	}
	gd->num_doors = i;
}

float	get_door_offset(t_gdata *gd, int x, int y)
{
	int		i;

	i = 0;
	while (i < gd->num_doors)
	{
		if (gd->door[i].x == x && gd->door[i].y == y)
			return (gd->door[i].offset);
		i++;
	}
	return (0);
}

void	open_sesame(t_gdata *gd)
{
	int		i;
	int		dx;
	int		dy;
	double	dist;

	i = 0;
	while (i < gd->num_doors)
	{
		dx = (int)gd->player.pos.x - gd->door[i].x;
		dy = (int)gd->player.pos.y - gd->door[i].y;
		dist = sqrt(dx * dx + dy * dy);
		if (dist <= 2.0)
		{
			if (gd->door[i].status == 0)
				gd->door[i].status = 2;
		}
		else
		{
			if (gd->door[i].status == 1)
				gd->door[i].status = 3;
		}
		i++;
	}
}

void	wall_anim(t_gdata *gd)
{
	int			i;

	i = 0;
	while (i < gd->num_doors)
	{
		if (gd->old_time == 0)
			gd->door[i].old_time = gd->time;
		if (gd->door[i].status == 2)
		{
			if ((gd->time - gd->door[i].old_time) > 30000)
			{
				gd->door[i].offset += 0.1;
				gd->door[i].old_time = gd->time;
			}
			if (gd->door[i].offset >= 1.0)
				gd->door[i].status = 1;
		}
		else if (gd->door[i].status == 3)
		{
			if ((gd->time - gd->door[i].old_time) > 30000)
			{
				gd->door[i].offset -= 0.1;
				gd->door[i].old_time = gd->time;
			}
			if (gd->door[i].offset <= 0.0)
				gd->door[i].status = 0;
		}
		i++;
	}
}

// wall_pos: the point at which ray hits the wall
// x or y calculated based on direction
int	door_calc(t_gdata *gd, t_ray *ray, t_ipos *map_pos)
{
	double	door_dist;
	double	wall_pos;

	if (ray->side_hit == RAY_HIT_N_OR_S)
	{
		door_dist = (map_pos->x - gd->player.pos.x + (1 - ray->step.x) / 2)
			/ ray->dir.x;
		wall_pos = gd->player.pos.y + door_dist * ray->dir.y;
		wall_pos -= floor(wall_pos);
		if (wall_pos < (1.0 - get_door_offset(gd, map_pos->x, map_pos->y)))
		{
			ray->hit_door = 1;
			return (1);
		}
	}
	else
	{
		door_dist = (map_pos->y - gd->player.pos.y + (1 - ray->step.y) / 2)
			/ ray->dir.y;
		wall_pos = gd->player.pos.x + door_dist * ray->dir.x;
		wall_pos -= floor(wall_pos);
		if (wall_pos < (1.0 - get_door_offset(gd, map_pos->x, map_pos->y)))
		{
			ray->hit_door = 1;
			return (1);
		}
	}
	return (0);
}
