/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-22 15:52:09 by abhi              #+#    #+#             */
/*   Updated: 2025-07-22 15:52:09 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <X11/Xlib.h>

static void	ray_calc_side_dist(t_gdata *gd, t_ray *ray, t_ipos *map_pos);
static int	line_height(t_gdata *gd, t_ray *ray);
static void	calc_draw_distance(t_ray *ray);

void	weapon_shoot(t_gdata *gd)
{
	static int		old_time;
	
	if (!old_time)
		old_time = gd->time;
	if (gd->weapon_state == 1)
	{
		if (gd->time - old_time > 50000)
		{
			gd->weapon_frame++;
			old_time = gd->time;
		}
		if (gd->weapon_frame == 5)
		{
			gd->weapon_state = 0;
			gd->weapon_frame = 0;
		}
	}
}

void	weapon_holster(t_gdata *gd)
{
	static int		old_time;
	
	if (!old_time)
		old_time = gd->time;
	if (gd->time - old_time > 50000)
	{
		gd->weapon_frame--;
		old_time = gd->time;
	}
	if (gd->weapon_frame == -1)
	{
		gd->weapon_state = -1;
		gd->weapon_frame = 0;
	}
}


void	weapon_equip(t_gdata *gd)
{
	static int		old_time;
	
	if (!old_time)
		old_time = gd->time;
	if (gd->time - old_time > 50000)
	{
		gd->weapon_frame++;
		old_time = gd->time;
	}
	if (gd->weapon_frame == 2)
	{
		gd->weapon_state = 0;
		gd->weapon_frame = 0;
	}
}

void	weapon_animate(t_gdata *gd)
{
	if (gd->weapon_state == -1)
		return ;
	if (gd->weapon_state == 1)
		weapon_shoot(gd);
	if (gd->weapon_state == 2)
		weapon_equip(gd);
	if (gd->weapon_state == 3)
		weapon_holster(gd);
	draw_weapon(gd);
}

int	mouse_move(t_gdata *gd)
{
	int	x, y;
	double		rot_speed;

	rot_speed = gd->frame_time * 3.0 * 8;
	mlx_mouse_get_pos(gd->mlx, gd->win, &x, &y);
	if (x < W_WIDTH / 3)
		rotate_player(gd, -rot_speed);
	else if (x > (W_WIDTH  * 2 / 3))
		rotate_player(gd, rot_speed);
	return (0);
}


int	rendering_function(void *param)
{
	t_gdata	*gd;
	t_ray	ray;
	t_ipos	map_pos;
	int		x;

	gd = (t_gdata *)param;
	// TODO: add logic to correctly handle RGB instead of texture
	floor_cast(gd);
	x = -1;
	while (++x < W_WIDTH)
	{
		map_pos = pos_dtoi(gd->player.pos);
		ray = ray_create(gd, x, &map_pos);
		ray_calc_side_dist(gd, &ray, &map_pos);
		ray.line_height = line_height(gd, &ray);
		calc_draw_distance(&ray);
		gd->z_buffer[x] = ray.perp_dist;
		draw_wall(gd, ray, x);
	}
	render_minimap(gd);
	draw_sprite(gd);
	open_sesame(gd);
	wall_anim(gd);
	weapon_animate(gd);
	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);
	update_frame_time(gd);
	handle_key_presses(gd);
	mouse_move(gd);
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
