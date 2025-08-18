/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:52:09 by abhi              #+#    #+#             */
/*   Updated: 2025/08/11 17:49:07 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <X11/Xlib.h>

static void	ray_calc_side_dist(t_gdata *gd, t_ray *ray, t_ipos *map_pos);
static void	calc_draw_distance(t_gdata *gd, t_ray *ray);
static int	mouse_move(t_gdata *gd);

int	render_loop(void *param)
{
	t_gdata	*gd;
	t_ray	ray;
	t_ipos	map_pos;
	int		x;

	gd = (t_gdata *)param;
	floor_cast(gd);
	x = -1;
	while (++x < W_WIDTH)
	{
		map_pos = pos_dtoi(gd->player.pos);
		ray = ray_create(gd, x, &map_pos);
		ray_calc_side_dist(gd, &ray, &map_pos);
		calc_draw_distance(gd, &ray);
		gd->z_buffer[x] = ray.perp_dist;
		draw_wall(gd, ray, x);
	}
	(render_minimap(gd), draw_sprite(gd));
	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);
	(open_sesame(gd), wall_anim(gd));
	weapon_animate(gd);
	handle_key_presses(gd);
	mouse_move(gd);
	update_frame_time(gd);
	return (1);
}

static int	mouse_move(t_gdata *gd)
{
	int		x;
	int		y;

	mlx_mouse_get_pos(gd->mlx, gd->win, &x, &y);
	if (x != W_WIDTH / 2)
		rotate_player(gd, (x - W_WIDTH / 2.0) * gd->frame_time);
	if (y != W_HEIGHT / 2)
	{
		gd->pitch -= (y - W_HEIGHT / 2.0);
		if (gd->pitch < -200)
			gd->pitch = -200;
		if (gd->pitch > 200)
			gd->pitch = 200;
	}
	mlx_mouse_move(gd->mlx, gd->win, W_WIDTH / 2, W_HEIGHT / 2);
	return (0);
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
	int		cell;

	while (42)
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
		cell = map_get(gd, map_pos->x, map_pos->y);
		if (cell == MAP_WALL)
			break ;
		else if (cell == 'D' && door_calc(gd, ray, map_pos))
			break ;
	}
}

// calculates draw_start and draw_end distances for each ray, which is then
// passed onto the paint_walls function
// doing so requires calculating line_height and perp_dist, which will be
// used later, so the calculation is stored in t_ray struct
//
// updates:
//		ray->draw_start
//		ray->draw_end
// 		ray->perp_dist
// 		ray->line_height
//	Returns: height of line to draw on screen
static void	calc_draw_distance(t_gdata *gd, t_ray *ray)
{
	if (ray->side_hit == RAY_HIT_N_OR_S)
		ray->perp_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_dist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_height = (int)(W_HEIGHT / ray->perp_dist);
	ray->draw_start = -ray->line_height / 2 + W_HEIGHT / 2 + (int)gd->pitch;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + W_HEIGHT / 2 + (int)gd->pitch;
	if (ray->draw_end >= W_HEIGHT)
		ray->draw_end = W_HEIGHT - 1;
}
