/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hits_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:00:11 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 22:00:35 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	perform DDA
//
//	from the position stored in map_pos, will advance in the direction of the
//	ray until a wall is hit
int	ray_hits_map(t_gdata *gd, t_ray *ray, t_ipos *map_pos)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			map_pos->x += ray->step.x;
			ray->side_hit = RAY_HIT_N_OR_S;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			map_pos->y += ray->step.y;
			ray->side_hit = RAY_HIT_E_OR_W;
		}
		if (map_get(gd, map_pos->x, map_pos->y) == MAP_WALL)
			hit = 1;
	}
	return (hit);
}
