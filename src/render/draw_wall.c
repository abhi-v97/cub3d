/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:27:41 by avalsang          #+#    #+#             */
/*   Updated: 2025/07/09 22:24:02 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texinfo_dir(t_ray *ray);
static void	set_texinfo(t_gdata *data, t_ray ray, t_texinfo *texinfo);

// function that draws the vertical line representing the wall that the ray
// collided with
// y: the pixel y-coordinate of the window, aka the vertical line drawn by the
// ray
// texinfo: struct that contains variables used to calculate texture data
// tex: struct with x and y which are coordinates of the texture array, used to
// grab the correct colour from the texture array
// texet = texture pixel
void	draw_wall(t_gdata *data, t_ray ray, int x)
{
	int			y;
	int			texel;
	t_texinfo	texinfo;
	t_ipos		tex;

	set_texinfo(data, ray, &texinfo);
	tex.x = (int)(texinfo.wall_x * data->tex_size);
	if ((ray.side_hit == 0 && ray.dir.x > 0)
		|| (ray.side_hit == 1 && ray.dir.y < 0))
		tex.x = data->tex_size - tex.x - 1;
	y = ray.draw_start;
	while (y < ray.draw_end)
	{
		tex.y = (int)texinfo.tex_pos & (data->tex_size - 1);
		texinfo.tex_pos += texinfo.step;
		texel = data->tex_size * tex.y + (data->tex_size - tex.x);
		put_pixel(&data->canvas, x, y++,
			data->textures[texinfo.dir][texel]);
	}
}

// dir: the cardinal direction of the ray, usedd to pick the correct texture
// wall_x: the exact point at which the ray hit the wall
// step: governs how to loop over the texture array, so that textures are drawn
// evenly and in full
// tex_pos: starting and current location of where we are in the texture array
static inline void	set_texinfo(t_gdata *data, t_ray ray, t_texinfo *texinfo)
{
	texinfo->dir = set_texinfo_dir(&ray);
	if (ray.side_hit == RAY_HIT_N_OR_S)
		texinfo->wall_x = data->player.pos.y + ray.perp_dist * ray.dir.y;
	else
		texinfo->wall_x = data->player.pos.x + ray.perp_dist * ray.dir.x;
	texinfo->wall_x -= floor(texinfo->wall_x);
	texinfo->step = (1.0 * data->tex_size / ray.line_height);
	texinfo->tex_pos = (ray.draw_start - W_HEIGHT / 2.0
			+ ray.line_height / 2.0) * texinfo->step;
}

static int	set_texinfo_dir(t_ray *ray)
{
	if (ray->side_hit == RAY_HIT_E_OR_W)
	{
		if (ray->dir.y < 0)
			return (NORTH);
		else
			return (SOUTH);
	}
	else
	{
		if (ray->dir.x < 0)
			return (WEST);
		else
			return (EAST);
	}
}
