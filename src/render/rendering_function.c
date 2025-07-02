/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:23:16 by aistok            #+#    #+#             */
/*   Updated: 2025/07/02 16:37:31 by aistok           ###   ########.fr       */
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

// 1. calculate ray position and direction
//    camera_x - x-coordinate in camera space
//    length of ray from one x or y-side to next x or y-side
//    these are derived as:
//    deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
//    deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
//    which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
//    where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
//    unlike (dirX, dirY) is not 1, however this does not matter, only the
//    ratio between deltaDistX and deltaDistY matters, due to the way the DDA
//    stepping further below works. So the values can be computed as below.
//    Division through zero is prevented, even though technically that's not
//    needed in C++ with IEEE 754 floating point values.
t_ray	ray_create(t_gdata *gd, int x, t_ipos map_pos)
{
	t_ray	ray;
	double	camera_x;

	camera_x = 2 * x / (double)W_WIDTH - 1;
	ray.dir.x = gd->dir.x + gd->plane.x * camera_x;
	ray.dir.y = gd->dir.y + gd->plane.y * camera_x;
	ray.delta_dist.x = (ray.dir.x == 0) ? 1e30 : fabs(1 / ray.dir.x);
	ray.delta_dist.y = (ray.dir.y == 0) ? 1e30 : fabs(1 / ray.dir.y);
	if (ray.dir.x < 0)
	{
		ray.step.x = -1;
		ray.side_dist.x = (gd->player.pos.x - map_pos.x) * ray.delta_dist.x;
	}
	else
	{
		ray.step.x = 1;
		ray.side_dist.x = (map_pos.x + 1.0 - gd->player.pos.x) * ray.delta_dist.x;
	}
	if (ray.dir.y < 0)
	{
		ray.step.y = -1;
		ray.side_dist.y = (gd->player.pos.y - map_pos.y) * ray.delta_dist.y;
	}
	else
	{
		ray.step.y = 1;
		ray.side_dist.y = (map_pos.y + 1.0 - gd->player.pos.y) * ray.delta_dist.y;
	}
	return (ray);
}

// perform DDA
// TO-DO: if (gd->map[map_pos.y][map_pos.x] > '0')
//        ARE VALUES IN THE .cub file all greater than
//        '0' (48)
//        and:
//        ' ' (32)
//        '-' (45)
int	ray_hits_map(t_gdata *gd, t_ray *ray, t_ipos *map_pos)
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
	return (hit);
}

//	Returns: height of line to draw on screen
int	line_height(t_gdata *gd, const t_ray *ray)
{
	double	perp_wall_dist;
	int		line_height;

	(void) gd;
	if (ray->side_hit == RAY_HIT_N_OR_S)
		perp_wall_dist = (ray->side_dist.x - ray->delta_dist.x);
	else
		perp_wall_dist = (ray->side_dist.y - ray->delta_dist.y);

	line_height = (int)(W_HEIGHT / perp_wall_dist);
	return (line_height);
}

//calculate lowest pixel to fill in current stripe
int	calc_line_start_y(int line_height)
{
	int draw_start;

	draw_start = -line_height / 2 + W_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

//calculate highest pixel to fill in current stripe
int	calc_line_end_y(int line_height)
{
	int	draw_end;

	draw_end = line_height / 2 + W_HEIGHT / 2;
	if (draw_end >= W_HEIGHT)
		draw_end = W_HEIGHT - 1;
	return (draw_end);
}

//	update gd->frame_time
//		timing for input and FPS counter
//		frameTime is the time this frame has taken to generate (in seconds)
void	update_frame_time(t_gdata *gd)
{
	gd->old_time = gd->time;
	gd->time = get_time_stamp();
	gd->frame_time = (gd->time - gd->old_time) / 10000000.0;
	// printf("FPS = %f\n", 1.0 / frameTime); //FPS counter
}

int	rendering_function(void *param)
{
	t_gdata *gd;
	t_ray	ray;
	t_ipos	map_pos;
	int		x;

	gd = (t_gdata *)param;
	fill_all(&gd->canvas, 0x00112233);
	x = -1;
	while (++x < W_WIDTH)
	{
		map_pos.x = (int)gd->player.pos.x;
		map_pos.y = (int)gd->player.pos.y;
		ray = ray_create(gd, x, map_pos);
		int color = 0x0000FF00;
		if (ray_hits_map(gd, &ray, &map_pos))
		{
			if (ray.side_hit == RAY_HIT_E_OR_W)
				color = color / 2;
			int l_height = line_height(gd, &ray);
			put_ver_line(&gd->canvas, x, \
				calc_line_start_y(l_height), calc_line_end_y(l_height), color);
		}
	}
	update_frame_time(gd);
	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);	
	handle_key_presses(gd);
	return (1);
}
