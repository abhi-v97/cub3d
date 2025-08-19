/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:01:57 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:20:40 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_calc_step_x_and_side_dist_x(
				t_gdata *gd, t_ray *ray, int map_pos_x);
static void	ray_calc_step_y_and_side_dist_y(
				t_gdata *gd, t_ray *ray, int map_pos_y);
/*
 * calculate ray position and direction
 * camera_x - x-coordinate in camera space
 * length of ray from one x or y-side to next x or y-side
 * these are derived as:
 * deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
 * deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
 * which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
 * where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
 * unlike (dirX, dirY) is not 1, however this does not matter, only the
 * ratio between deltaDistX and deltaDistY matters, due to the way the DDA
 * stepping further below works. So the values can be computed as below.
 * Division through zero is prevented, even though technically that's not
 * needed in C++ with IEEE 754 floating point values.
 */

t_ray	ray_create(t_gdata *gd, int x, t_ipos *map_pos)
{
	t_ray	ray;
	double	camera_x;

	camera_x = 2 * x / (double)W_WIDTH - 1;
	ray.dir.x = gd->dir.x + gd->plane.x * camera_x;
	ray.dir.y = gd->dir.y + gd->plane.y * camera_x;
	if (ray.dir.x == 0)
		ray.delta_dist.x = 1e30;
	else
		ray.delta_dist.x = fabs(1 / ray.dir.x);
	if (ray.dir.y == 0)
		ray.delta_dist.y = 1e30;
	else
		ray.delta_dist.y = fabs(1 / ray.dir.y);
	ray_calc_step_x_and_side_dist_x(gd, &ray, map_pos->x);
	ray_calc_step_y_and_side_dist_y(gd, &ray, map_pos->y);
	return (ray);
}

static void	ray_calc_step_x_and_side_dist_x(
		t_gdata *gd, t_ray *ray, int map_pos_x)
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

static void	ray_calc_step_y_and_side_dist_y(
		t_gdata *gd, t_ray *ray, int map_pos_y)
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
