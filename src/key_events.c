/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:14:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 17:13:19 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdbool.h>

void handle_key_presses(t_gdata *gd) {
	double moveSpeed =
			gd->frame_time * 5.0 * 8; // the constant value is in squares/second
	double rotSpeed =
			gd->frame_time * 3.0 * 4; // the constant value is in radians/second

	// move forward if no wall in front of you
	if (gd->keys[KEY_UP]) {
		// if (gd->map[(int)gd->player.pos.y]
		//[(int)(gd->player.pos.x + gd->dir.x * moveSpeed)] == false)
		gd->player.pos.x += gd->dir.x * moveSpeed;
		// if (gd->map[(int)(gd->player.pos.y + gd->dir.y * moveSpeed)]
		//[(int)gd->player.pos.x] == false)
		gd->player.pos.y += gd->dir.y * moveSpeed;
		// if (gd->map[(int)(gd->player.pos.y + gd->dir.y * moveSpeed)]
		//[(int)(gd->player.pos.x)] == false)
		// gd->player.pos.y += gd->dir.y * moveSpeed;
		// if (gd->map[(int)gd->player.pos.y]
		//[(int)(gd->player.pos.x + gd->dir.y * moveSpeed)] == false)
		// gd->player.pos.y += gd->dir.y * moveSpeed;
	}

	// move backwards if no wall behind you
	if (gd->keys[KEY_DOWN]) {
		// if (gd->map[(int)gd->player.pos.y]
		//[(int)(gd->player.pos.x - gd->dir.x * moveSpeed)] == false)
		gd->player.pos.x -= gd->dir.x * moveSpeed;
		// if (gd->map[(int)(gd->player.pos.y - gd->dir.y * moveSpeed)]
		//[(int)gd->player.pos.x] == false)
		gd->player.pos.y -= gd->dir.y * moveSpeed;
	}

	if (gd->keys[KEY_A]) {
		double facing_dir = atan2(gd->dir.y, gd->dir.x);
		double cos_val = cos(facing_dir + M_PI_2);
		double sin_val = sin(facing_dir + M_PI_2);
		if (gd->map[(int)gd->player.pos.y]
							 [(int)(gd->player.pos.x + cos_val * moveSpeed)] == false)
			gd->player.pos.x += cos_val * moveSpeed;
		if (gd->map[(int)(gd->player.pos.y + sin_val * moveSpeed)]
							 [(int)gd->player.pos.x] == false)
			gd->player.pos.y += sin_val * moveSpeed;
	}

	if (gd->keys[KEY_D]) {
		double facing_dir = atan2(gd->dir.y, gd->dir.x);
		double cos_val = cos(facing_dir - M_PI_2);
		double sin_val = sin(facing_dir - M_PI_2);
		if (gd->map[(int)gd->player.pos.y]
							 [(int)(gd->player.pos.x + cos_val * moveSpeed)] == false)
			gd->player.pos.x += cos_val * moveSpeed;
		if (gd->map[(int)(gd->player.pos.y + sin_val * moveSpeed)]
							 [(int)gd->player.pos.x] == false)
			gd->player.pos.y += sin_val * moveSpeed;
	}

	// rotate to the right
	if (gd->keys[KEY_RIGHT] || mouse_moving_right(gd)) {
		// both camera direction and camera plane must be rotated
		double oldDirX = gd->dir.x;
		gd->dir.x = gd->dir.x * cos(-rotSpeed) - gd->dir.y * sin(-rotSpeed);
		gd->dir.y = oldDirX * sin(-rotSpeed) + gd->dir.y * cos(-rotSpeed);
		double oldPlaneX = gd->plane.x;
		gd->plane.x = gd->plane.x * cos(-rotSpeed) - gd->plane.y * sin(-rotSpeed);
		gd->plane.y = oldPlaneX * sin(-rotSpeed) + gd->plane.y * cos(-rotSpeed);
	}

	// rotate to the left
	if (gd->keys[KEY_LEFT] || mouse_moving_left(gd)) {
		// both camera direction and camera plane must be rotated
		double oldDirX = gd->dir.x;
		gd->dir.x = gd->dir.x * cos(rotSpeed) - gd->dir.y * sin(rotSpeed);
		gd->dir.y = oldDirX * sin(rotSpeed) + gd->dir.y * cos(rotSpeed);
		double oldPlaneX = gd->plane.x;
		gd->plane.x = gd->plane.x * cos(rotSpeed) - gd->plane.y * sin(rotSpeed);
		gd->plane.y = oldPlaneX * sin(rotSpeed) + gd->plane.y * cos(rotSpeed);
	}
}

int key_press(int key, t_gdata *gd) {
	if (key == k_DOWN || key == k_S)
		gd->keys[KEY_DOWN] = true;
	else if (key == k_UP || key == k_W)
		gd->keys[KEY_UP] = true;
	else if (key == k_RIGHT)
		gd->keys[KEY_RIGHT] = true;
	else if (key == k_LEFT)
		gd->keys[KEY_LEFT] = true;
	else if (key == k_D)
		gd->keys[KEY_D] = true;
	else if (key == k_A)
		gd->keys[KEY_A] = true;
	return (1);
}

int key_release(int key, t_gdata *gd) {
	if (key == k_ESC)
		mlx_loop_end(gd->mlx);
	else if (key == k_DOWN || key == k_S)
		gd->keys[KEY_DOWN] = false;
	else if (key == k_UP || key == k_W)
		gd->keys[KEY_UP] = false;
	else if (key == k_RIGHT)
		gd->keys[KEY_RIGHT] = false;
	else if (key == k_LEFT)
		gd->keys[KEY_LEFT] = false;
	else if (key == k_D)
		gd->keys[KEY_D] = false;
	else if (key == k_A)
		gd->keys[KEY_A] = false;
	return (1);
}
