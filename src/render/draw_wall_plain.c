/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_plain.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:58:39 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 21:58:57 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_plain(t_gdata *gd, t_ray *ray, int x, int color)
{
	if (ray->side_hit == RAY_HIT_E_OR_W)
		color = color / 2;
	put_ver_line(&gd->canvas, x, ray->draw_start, ray->draw_end, color);
}
