/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:23:16 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:22:38 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	ray_calc_side_dist(t_gdata *gd, t_ray *ray, t_ipos *map_pos);
static int	line_height(t_gdata *gd, t_ray *ray);
static void	calc_draw_distance(t_ray *ray);
static void	draw_bg(t_gdata *gd, t_ray *ray, int x);

int	rendering_function(void *param)
{
	t_gdata	*gd;
	t_ray	ray;
	t_ipos	map_pos;
	int		x;

	gd = (t_gdata *)param;
	x = -1;
	while (++x < W_WIDTH)
	{
		map_pos = pos_dtoi(gd->player.pos);
		ray = ray_create(gd, x, &map_pos);
		ray_calc_side_dist(gd, &ray, &map_pos);
		ray.line_height = line_height(gd, &ray);
		calc_draw_distance(&ray);
		draw_bg(gd, &ray, x);
		draw_wall(gd, ray, x);
	}
	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);
	update_frame_time(gd);
	handle_key_presses(gd);
	return (1);
}

//	perform DDA
//
//	from the position stored in map_pos, will advance in the direction of the
//	ray until a wall is hit, updating:
//		ray->side_dist.x
//		ray->side_dist.y
//		day->side_hit
static void	ray_calc_side_dist(t_gdata *gd, t_ray *ray, t_ipos *map_pos)
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
}

//	Returns: height of line to draw on screen
static int	line_height(t_gdata *gd, t_ray *ray)
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

// calculates draw_start and draw_end distances for each ray, which is then
// passed onto the paint_walls function
//
// updates:
//		ray->draw_start
//		ray->draw_end
static void	calc_draw_distance(t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + W_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + W_HEIGHT / 2;
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = W_HEIGHT - 1;
}

static void	draw_bg(t_gdata *gd, t_ray *ray, int x)
{
	int	start;
	int	end;

	start = ray->draw_start;
	while (start >= 0)
		put_pixel(&gd->canvas, x, start--, gd->tex_rgb[CEILING]);
	end = ray->draw_end;
	while (end <= W_HEIGHT)
		put_pixel(&gd->canvas, x, end++, gd->tex_rgb[FLOOR]);
}
