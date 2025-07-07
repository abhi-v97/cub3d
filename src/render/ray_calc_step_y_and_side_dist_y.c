/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_step_y_and_side_dist_y.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:00:56 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 22:01:12 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_calc_step_y_and_side_dist_y(t_gdata *gd, t_ray *ray, int map_pos_y)
{
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (gd->player.pos.y - map_pos_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y
			= (map_pos_y + 1.0 - gd->player.pos.y) * ray->delta_dist.y;
	}
}
