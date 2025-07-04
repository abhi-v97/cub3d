/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:14:09 by aistok            #+#    #+#             */
/*   Updated: 2025/07/02 15:19:49 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

/*
 *	the constant values in move_speed are in squares/second
 *	and for the rot_speed in radians/second
 */
void handle_key_presses(t_gdata *gd) {
	double move_speed = gd->frame_time * 5.0 * 8;
	double rot_speed = gd->frame_time * 3.0 * 4;

	// move forward if no wall in front of you
	if (gd->keys[KEY_UP])
	{
		int x;
		int y;

		x = (int)(gd->player.pos.x + gd->dir.x * move_speed);
		y = (int)(gd->player.pos.y);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.x += gd->dir.x * move_speed;
		x = (int)(gd->player.pos.x);
		y = (int)(gd->player.pos.y + gd->dir.y * move_speed);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.y += gd->dir.y * move_speed;
	}

	// move backwards if no wall behind you
	if (gd->keys[KEY_DOWN]) {
		int x;
		int y;

		x = (int)(gd->player.pos.x - gd->dir.x * move_speed);
		y = (int)(gd->player.pos.y);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.x -= gd->dir.x * move_speed;
		x = (int)(gd->player.pos.x);
		y = (int)(gd->player.pos.y - gd->dir.y * move_speed);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.y -= gd->dir.y * move_speed;
	}

	if (gd->keys[KEY_A]) {
		double facing_dir = atan2(gd->dir.y, gd->dir.x);
		double cos_val = cos(facing_dir + M_PI_2);
		double sin_val = sin(facing_dir + M_PI_2);
		int x;
		int y;

		x = (int)(gd->player.pos.x + cos_val * move_speed);
		y = (int)(gd->player.pos.y);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.x += cos_val * move_speed;
		x = (int)(gd->player.pos.x);
		y = (int)(gd->player.pos.y + sin_val * move_speed);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.y += sin_val * move_speed;
	}

	if (gd->keys[KEY_D]) {
		double facing_dir = atan2(gd->dir.y, gd->dir.x);
		double cos_val = cos(facing_dir - M_PI_2);
		double sin_val = sin(facing_dir - M_PI_2);
		int x;
		int y;

		x = (int)(gd->player.pos.x + cos_val * move_speed);
		y = (int)(gd->player.pos.y);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.x += cos_val * move_speed;
		x = (int)(gd->player.pos.x);
		y = (int)(gd->player.pos.y + sin_val * move_speed);
		if (map_get(gd, x, y) != MAP_WALL)
			gd->player.pos.y += sin_val * move_speed;
	}

	// rotate to the right
	// if (gd->keys[KEY_RIGHT] || mouse_moving_right(gd)) {
	if (gd->keys[KEY_RIGHT]) {
		// both camera direction and camera plane must be rotated
		double oldDirX = gd->dir.x;
		gd->dir.x = gd->dir.x * cos(-rot_speed) - gd->dir.y * sin(-rot_speed);
		gd->dir.y = oldDirX * sin(-rot_speed) + gd->dir.y * cos(-rot_speed);
		double oldPlaneX = gd->plane.x;
		gd->plane.x = gd->plane.x * cos(-rot_speed) - gd->plane.y * sin(-rot_speed);
		gd->plane.y = oldPlaneX * sin(-rot_speed) + gd->plane.y * cos(-rot_speed);
	}

	// rotate to the left
	// if (gd->keys[KEY_LEFT] || mouse_moving_left(gd)) {
	if (gd->keys[KEY_LEFT]) {
		// both camera direction and camera plane must be rotated
		double oldDirX = gd->dir.x;
		gd->dir.x = gd->dir.x * cos(rot_speed) - gd->dir.y * sin(rot_speed);
		gd->dir.y = oldDirX * sin(rot_speed) + gd->dir.y * cos(rot_speed);
		double oldPlaneX = gd->plane.x;
		gd->plane.x = gd->plane.x * cos(rot_speed) - gd->plane.y * sin(rot_speed);
		gd->plane.y = oldPlaneX * sin(rot_speed) + gd->plane.y * cos(rot_speed);
	}
}

void	debug_print(t_gdata *data)
{
	printf("dir x =%f\n", data->dir.x);
	printf("dir y =%f\n", data->dir.y);
}

int key_press(int key, t_gdata *gd) {
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

int key_release(int key, t_gdata *gd) {
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
