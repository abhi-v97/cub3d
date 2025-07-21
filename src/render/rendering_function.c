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
#include <X11/Xlib.h>
#include <math.h>

static void	ray_calc_side_dist(t_gdata *gd, t_ray *ray, t_ipos *map_pos);
static int	line_height(t_gdata *gd, t_ray *ray);
static void	calc_draw_distance(t_ray *ray);

void	open_sesame(t_gdata *gd)
{
	for (int i = 0; i < gd->num_doors; i++)
	{
		int dx = (int)gd->player.pos.x - gd->door[i].x;
		int dy = (int)gd->player.pos.y - gd->door[i].y;
		double dist = sqrt(dx * dx + dy * dy);
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
	}
}

void	wall_anim(t_gdata *gd)
{
	int		i;
	static int	time;

	i = 0;
	time = get_time_stamp();
	while (i < gd->num_doors)
	{
		if (gd->old_time == 0)
			gd->door[i].old_time = time;
		if (gd->door[i].status == 2)
		{
			if ((time - gd->door[i].old_time) > 30000)
			{
				gd->door[i].offset += 0.1;
				gd->door[i].old_time = time;
			}
			if (gd->door[i].offset >= 1.0)
				gd->door[i].status = 1;
		}
		else if (gd->door[i].status == 3)
		{
			if ((time - gd->door[i].old_time) > 30000)
			{
				gd->door[i].offset -= 0.1;
				gd->door[i].old_time = time;
			}
			if (gd->door[i].offset <= 0.0)
				gd->door[i].status = 0;
		}
		i++;
	}
}

int	rendering_function(void *param)
{
	t_gdata	*gd;
	t_ray	ray;
	t_ipos	map_pos;
	int		x;

	gd = (t_gdata *)param;
	render_background(gd);
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
	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);
	update_frame_time(gd);
	handle_key_presses(gd);
	return (1);
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
	return (0.0);
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
		int cell = map_get(gd, map_pos->x, map_pos->y);
        if (cell == MAP_WALL)
            hit = 1;
        else if (cell == 'D')
        {
			double door_dist;
			double wall_x;
			double wall_y;

			if (ray->side_hit == RAY_HIT_N_OR_S)
			{
				door_dist = (map_pos->x - gd->player.pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
				wall_y = gd->player.pos.y + door_dist * ray->dir.y;
				wall_y -= floor(wall_y);
				if (wall_y < (1.0 - get_door_offset(gd, map_pos->x, map_pos->y)))
				{
					hit = 1;
					ray->perp_dist = door_dist;
					ray->hit_door = 1;
				}
			}
			else
			{
				door_dist = (map_pos->y - gd->player.pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
				wall_x = gd->player.pos.x + door_dist * ray->dir.x;
				wall_x -= floor(wall_x);
				if (wall_x < (1.0 - get_door_offset(gd, map_pos->x, map_pos->y)))
				{
					hit = 1;
					ray->perp_dist = door_dist;
					ray->hit_door = 1;
				}
        }
	}
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
