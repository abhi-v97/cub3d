/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calc_step_x_and_side_dist_x.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:01:21 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 22:01:41 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_calc_step_x_and_side_dist_x(t_gdata *gd, t_ray *ray, int map_pos_x)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (gd->player.pos.x - map_pos_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x
			= (map_pos_x + 1.0 - gd->player.pos.x) * ray->delta_dist.x;
	}
}
