/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:14:09 by aistok            #+#    #+#             */
/*   Updated: 2025/07/06 13:10:40 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

static void	move_player(t_gdata *gd, double dx, double dy, double move_speed);
static void	rotate_player(t_gdata *gd, double rot_speed);

int	key_press(int key, t_gdata *gd)
{
	if (key == XK_Down || key == XK_s)
		gd->keys[KEY_DOWN] = true;
	else if (key == XK_Up || key == XK_w)
		gd->keys[KEY_UP] = true;
	else if (key == XK_Right)
		gd->keys[KEY_RIGHT] = true;
	else if (key == XK_Left)
		gd->keys[KEY_LEFT] = true;
	else if (key == XK_d)
		gd->keys[KEY_D] = true;
	else if (key == XK_a)
		gd->keys[KEY_A] = true;
	else if (key == XK_p)
		debug_print(gd);
	return (1);
}

int	key_release(int key, t_gdata *gd)
{
	if (key == XK_Escape)
		mlx_loop_end(gd->mlx);
	else if (key == XK_Down || key == XK_s)
		gd->keys[KEY_DOWN] = false;
	else if (key == XK_Up || key == XK_w)
		gd->keys[KEY_UP] = false;
	else if (key == XK_Right)
		gd->keys[KEY_RIGHT] = false;
	else if (key == XK_Left)
		gd->keys[KEY_LEFT] = false;
	else if (key == XK_d)
		gd->keys[KEY_D] = false;
	else if (key == XK_a)
		gd->keys[KEY_A] = false;
	return (1);
}

/*
 *	the constant values in move_speed are in squares/second
 *	and for the rot_speed in radians/second
 */
void	handle_key_presses(t_gdata *gd)
{
	double		move_speed;
	double		rot_speed;

	move_speed = gd->frame_time * 5.0 * 8;
	rot_speed = gd->frame_time * 3.0 * 8;
	if (gd->keys[KEY_UP])
		move_player(gd, gd->dir.x, gd->dir.y, move_speed);
	if (gd->keys[KEY_DOWN])
		move_player(gd, -gd->dir.x, -gd->dir.y, move_speed);
	if (gd->keys[KEY_A])
		move_player(gd, -gd->dir.y, gd->dir.x, move_speed);
	if (gd->keys[KEY_D])
		move_player(gd, gd->dir.y, -gd->dir.x, move_speed);
	if (gd->keys[KEY_RIGHT])
		rotate_player(gd, -rot_speed);
	if (gd->keys[KEY_LEFT])
		rotate_player(gd, rot_speed);
}

static void	move_player(t_gdata *gd, double dx, double dy, double move_speed)
{
	int		x;
	int		y;

	if (dx != 0)
	{
		x = (int)(gd->player.pos.x + dx * move_speed);
		y = (int)(gd->player.pos.y);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.x += dx * move_speed;
	}
	if (dy != 0)
	{
		x = (int)(gd->player.pos.x);
		y = (int)(gd->player.pos.y + dy * move_speed);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.y += dy * move_speed;
	}
}

static void	rotate_player(t_gdata *gd, double rot_speed)
{
	double		tmp;

	tmp = gd->dir.x;
	gd->dir.x = gd->dir.x * cos(rot_speed) - gd->dir.y * sin(rot_speed);
	gd->dir.y = tmp * sin(rot_speed) + gd->dir.y * cos(rot_speed);
	tmp = gd->plane.x;
	gd->plane.x = gd->plane.x * cos(rot_speed) - gd->plane.y * sin(rot_speed);
	gd->plane.y = tmp * sin(rot_speed) + gd->plane.y * cos(rot_speed);
}
