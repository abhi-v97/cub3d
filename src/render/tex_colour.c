/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-30 15:27:41 by avalsang          #+#    #+#             */
/*   Updated: 2025-06-30 15:27:41 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_dir(t_ray *ray);

// step: how much to increase texture coordinates per pixel
void	texture_func(t_gdata *data, t_ray ray, int x, int draw_start, int draw_end)
{
	int		y;
	double	tex_pos;
	double	step;
	int		color;
	int		dir = get_texture_dir(&ray);
	int		tex_x;
	int		tex_y;

	double wall_x;
	if (ray.side_hit == RAY_HIT_N_OR_S)
		wall_x = data->player.pos.y + ray.perp_dist * ray.dir.y;
	else
		wall_x = data->player.pos.x + ray.perp_dist * ray.dir.x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * data->tex_size);
	if ((ray.side_hit == 0 && ray.dir.x < 0) || (ray.side_hit == 1 && ray.dir.y < 0))
		tex_x = data->tex_size - tex_x - 1;

	y = draw_start;
	step = (1.0 * data->tex_size / ray.line_height);
	tex_pos = (draw_start - W_HEIGHT / 2.0 + ray.line_height / 2.0) * step;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (data->tex_size - 1);
		tex_pos += step;
		color = data->textures[dir][data->tex_size * tex_y + tex_x];
		put_pixel(&data->canvas, x, y++, color);
	}
}

static int	get_texture_dir(t_ray *ray)
{
	if (ray->side_hit == RAY_HIT_E_OR_W)
	{
		if (ray->dir.y < 0)
			return WEST;
		else
			return EAST;
	}
	else
	{
		if (ray->dir.x < 0)
			return NORTH;
		else
			return SOUTH;
	}
}
