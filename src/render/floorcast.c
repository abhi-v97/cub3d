/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-11 16:38:16 by abhi              #+#    #+#             */
/*   Updated: 2025-07-11 16:38:16 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/X.h>
#include <threads.h>

static void	draw_line(t_gdata *gd, t_floor *floor, int y);
static void	set_floorcast_info(t_gdata *gd, t_floor *floor, int y);
static void	set_texels(t_gdata *gd, t_floor *floor, int *tx, int *ty);

void	floor_cast(t_gdata *gd)
{
	int				y;
	t_floor			floor;

	floor.ray.dir.x = gd->dir.x - gd->plane.x;
	floor.ray.dir.y = gd->dir.y - gd->plane.y;
	y = 0;
	while (y < W_HEIGHT)
	{
		set_floorcast_info(gd, &floor, y);
		draw_line(gd, &floor, y);
		y++;
	}
}

static void	set_floorcast_info(t_gdata *gd, t_floor *floor, int y)
{
	floor->row_dist = (0.5 * W_HEIGHT) / (y - W_HEIGHT / 2.0);
	floor->step_x = floor->row_dist * (gd->dir.x + gd->plane.x
			- floor->ray.dir.x) / W_WIDTH;
	floor->step_y = floor->row_dist * (gd->dir.y + gd->plane.y
			- floor->ray.dir.y) / W_WIDTH;
	floor->floor_x = gd->player.pos.x + floor->row_dist * floor->ray.dir.x;
	floor->floor_y = gd->player.pos.y + floor->row_dist * floor->ray.dir.y;
}

static void	draw_line(t_gdata *gd, t_floor *floor, int y)
{
	int		x;
	int		tx;
	int		ty;
	int		colour;

	x = 0;
	while (x < W_WIDTH)
	{
		set_texels(gd, floor, &tx, &ty);
		floor->floor_x += floor->step_x;
		floor->floor_y += floor->step_y;
		colour = gd->textures[FLOOR][gd->tex_size * ty + tx];
		colour = (colour >> 1) & 8355711;
		put_pixel(&gd->canvas, x, y, colour);
		colour = gd->textures[CEILING][gd->tex_size * ty + tx];
		colour = (colour >> 1) & 8355711;
		put_pixel(&gd->canvas, x, W_HEIGHT - y - 1, colour);
		x++;
	}
}

static void	set_texels(t_gdata *gd, t_floor *floor, int *tx, int *ty)
{
	*tx = (int)(gd->tex_size * (floor->floor_x - (int)floor->floor_x))
		& (gd->tex_size - 1);
	*ty = (int)(gd->tex_size * (floor->floor_y - (int)floor->floor_y))
		& (gd->tex_size - 1);
}
