/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:59:46 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 22:00:01 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//	Returns: height of line to draw on screen
int	line_height(t_gdata *gd, t_ray *ray)
{
	int		line_height;

	(void) gd;
	if (ray->side_hit == RAY_HIT_N_OR_S)
		ray->perp_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_dist = (ray->side_dist.y - ray->delta_dist.y);

	line_height = (int)(W_HEIGHT / ray->perp_dist);
	return (line_height);
}
