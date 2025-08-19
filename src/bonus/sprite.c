/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-16 19:11:39 by abhi              #+#    #+#             */
/*   Updated: 2025-07-16 19:11:39 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render(t_gdata *gd, t_sprite *sp);
static void	put_sprite(t_gdata *gd, t_sprite *sp, int x, int tex_x);
static void	calc_sprite_info(t_gdata *gd, t_sprite *sp);

void	draw_sprite(t_gdata *gd)
{
	int			i;

	i = 0;
	while (i < gd->num_sprite_pos)
	{
		calc_sprite_info(gd, &gd->sprite[i]);
		render(gd, &gd->sprite[i]);
		i++;
	}
}

static void	render(t_gdata *gd, t_sprite *sp)
{
	int		x;
	int		tex_x;

	x = sp->draw_start_x;
	while (x < sp->draw_end_x)
	{
		tex_x = (((x + (sp->sprite_size >> 1) - sp->sprite_screen_x) << 8)
				* gd->tex_size / sp->sprite_size) >> 8;
		if (sp->transform_y > 0 && x > 0 && x < W_WIDTH && sp->transform_y
			< gd->z_buffer[x])
			put_sprite(gd, sp, x, tex_x);
		x++;
	}
}

static void	put_sprite(t_gdata *gd, t_sprite *sp, int x, int tex_x)
{
	int		y;
	int		tex_y;
	int		colour;

	y = sp->draw_start_y;
	while (y < sp->draw_end_y)
	{
		tex_y = (((((y - (int)gd->pitch) << 8) - (W_HEIGHT << 7)
						+ (sp->sprite_size << 7))
					* gd->tex_size) / sp->sprite_size) >> 8;
		colour = gd->sprite_tex[sp->tex][gd->tex_size * tex_y + tex_x];
		if ((colour & 0x00FFFFFF) != 0)
			put_pixel(&gd->canvas, x, y, colour);
		y++;
	}
}

static void	calc_sprite_info(t_gdata *gd, t_sprite *sp)
{
	sp->inv_det = 1.0 / (gd->plane.x * gd->dir.y - gd->dir.x
			* gd->plane.y);
	sp->transform_x = sp->inv_det * (gd->dir.y * (sp->x
				- gd->player.pos.x) - gd->dir.x * (sp->y
				- gd->player.pos.y));
	sp->transform_y = sp->inv_det * (-gd->plane.y * (sp->x
				- gd->player.pos.x) + gd->plane.x * (sp->y
				- gd->player.pos.y));
	sp->sprite_screen_x = (int)((W_WIDTH / 2.0) * (1 + sp->transform_x
				/ sp->transform_y));
	sp->sprite_size = abs((int)(W_HEIGHT / (sp->transform_y)));
	sp->draw_start_y = -sp->sprite_size / 2 + W_HEIGHT / 2 + (int)gd->pitch;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sprite_size / 2 + W_HEIGHT / 2 + (int)gd->pitch;
	if (sp->draw_end_y >= W_HEIGHT)
		sp->draw_end_y = W_HEIGHT - 1;
	sp->draw_start_x = -sp->sprite_size / 2 + sp->sprite_screen_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->sprite_size / 2 + sp->sprite_screen_x;
	if (sp->draw_end_x >= W_WIDTH)
		sp->draw_end_x = W_WIDTH - 1;
}
