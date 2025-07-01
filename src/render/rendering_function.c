/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:23:16 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 23:26:29 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

/*
int	rendering_function(void *param)
{
				t_gdata *gd = param;

				int *data = (int *)gd->canvas.addr;
				int i = 0;
				while (i < (int)(gd->canvas.w * gd->canvas.h))
								data[i++] = 0x00c8c8c8;

				// dummy code used to test textures
				test_textures(gd, gd->textures[NORTH], 100);
				test_textures(gd, gd->textures[WEST], 400);
				test_textures(gd, gd->textures[SOUTH], 700);
				test_textures(gd, gd->textures[EAST], 1000);

				mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);

				return (1);
}
*/

void player_set_direction(t_gdata *gd) {

	t_cardinal cardinal;
	static const double direction_consts[][4] = {
			{-1, 0, 0, 0.66}, {1, 0, 0, -0.66}, {0, 1, 0.66, 0}, {0, -1, -0.66, 0}};

	if (gd->player_direction == 'N') {
		cardinal = NORTH;
		printf("DIR is N\n"); // degub
	} else if (gd->player_direction == 'S') {
		cardinal = SOUTH;
		printf("DIR is S\n"); // degub
	} else if (gd->player_direction == 'E') {
		cardinal = EAST;
		printf("DIR is E\n"); // degub
	} else if (gd->player_direction == 'W') {
		cardinal = WEST;
		printf("DIR is W\n"); // degub
	}
	gd->dir.x = direction_consts[cardinal][DIRX];
	gd->dir.y = direction_consts[cardinal][DIRY];
	gd->plane.x = direction_consts[cardinal][PLANEX];
	gd->plane.y = direction_consts[cardinal][PLANEY];
	printf("dir.x = %f, dir.y = %f\n", gd->dir.x, gd->dir.y);				 // degub
	printf("plane.x = %f, plane.y = %f\n", gd->plane.x, gd->plane.y); // degub
}

int rendering_function(void *param) {
	t_gdata *gd;
	double camera_x;
	t_pos ray_dir;
	t_ipos map_pos;
	t_pos side_dist; // length of ray from current position to next x or y-side

	gd = (t_gdata *)param;
	int x;

	fill_all(&gd->canvas, 0x00112233);
	handle_key_presses(gd);
	mlx_mouse_get_pos(gd->mlx, gd->win, &gd->mpos_at_start.x,
										&gd->mpos_at_start.y);

	x = -1;
	while (++x < W_WIDTH) {
		// calculate ray position and direction
		camera_x = 2 * x / (double)W_WIDTH - 1; // x-coordinate in camera space
		ray_dir.x = gd->dir.x + gd->plane.x * camera_x;
		ray_dir.y = gd->dir.y + gd->plane.y * camera_x;
		// which box of the map we're in
		map_pos.x = (int)gd->player.pos.x;
		map_pos.y = (int)gd->player.pos.y;

		// length of ray from one x or y-side to next x or y-side
		// these are derived as:
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		// which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| /
		// rayDirY) where |rayDir| is the length of the vector (rayDirX, rayDirY).
		// Its length, unlike (dirX, dirY) is not 1, however this does not matter,
		// only the ratio between deltaDistX and deltaDistY matters, due to the way
		// the DDA stepping further below works. So the values can be computed as
		// below.
		//	Division through zero is prevented, even though technically that's not
		//	needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (ray_dir.x == 0) ? 1e30 : fabs(1 / ray_dir.x);
		double deltaDistY = (ray_dir.y == 0) ? 1e30 : fabs(1 / ray_dir.y);

		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;		// was a NS or a EW wall hit?
		// calculate step and initial sideDist
		if (ray_dir.x < 0) {
			stepX = -1;
			side_dist.x = (gd->player.pos.x - map_pos.x) * deltaDistX;
		} else {
			stepX = 1;
			side_dist.x = (map_pos.x + 1.0 - gd->player.pos.x) * deltaDistX;
		}
		if (ray_dir.y < 0) {
			stepY = -1;
			side_dist.y = (gd->player.pos.y - map_pos.y) * deltaDistY;
		} else {
			stepY = 1;
			side_dist.y = (map_pos.y + 1.0 - gd->player.pos.y) * deltaDistY;
		}

		// perform DDA
		while (hit == 0) {
			if (side_dist.x < side_dist.y) {
				side_dist.x += deltaDistX;
				map_pos.x += stepX;
				side = 0;
			} else {
				side_dist.y += deltaDistY;
				map_pos.y += stepY;
				side = 1;
			}
			// Check if ray has hit a wall
			if (gd->map[map_pos.y][map_pos.x] > '0')
				hit = 1;
		}
		// Calculate distance projected on camera direction. This is the shortest
		// distance from the point where the wall is hit to the camera plane.
		// Euclidean to center camera point would give fisheye effect! This can be
		// computed as (mapX - gd->player.pos.x + (1 - stepX) / 2) / rayDirX for
		// side == 0, or same formula with Y for size == 1, but can be simplified to
		// the code below thanks to how sideDist and deltaDist are computed: because
		// they were left scaled to |rayDir|. sideDist is the entire length of the
		// ray above after the multiple steps, but we subtract deltaDist once
		// because one step more into the wall was taken above.
		if (side == 0)
			perpWallDist = (side_dist.x - deltaDistX);
		else
			perpWallDist = (side_dist.y - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(W_HEIGHT / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + W_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + W_HEIGHT / 2;
		if (drawEnd >= W_HEIGHT)
			drawEnd = W_HEIGHT - 1;

		// choose wall color
		int color = 0x00FF00FF;
		/*
		switch (gd->map[map_pos.x][map_pos.y])
		{
						case 1:	color = RGB_Red;		break; //red
						case 2:	color = RGB_Green;		break; //green
						case 3:	color = RGB_Blue;		break; //blue
						case 4:	color = RGB_White;		break; //white
						default: color = RGB_Yellow;	break; //yellow
		}
		*/

		// give x and y sides different brightness
		if (side == 1)
			color = color / 2;

		// draw the pixels of the stripe as a vertical line
		put_ver_line(&gd->canvas, x, drawStart, drawEnd, color);
	}
	// timing for input and FPS counter
	gd->old_time = gd->time;
	gd->time = get_time_stamp();
	gd->frame_time =
			(gd->time - gd->old_time) /
			10000000.0; // frameTime is the time this frame has taken, in seconds
	// printf("FPS = %f\n", 1.0 / frameTime); //FPS counter

	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);

	return (1);
}
