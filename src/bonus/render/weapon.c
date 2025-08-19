/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 14:50:39 by abhi              #+#    #+#             */
/*   Updated: 2025/08/09 18:08:12 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*parse_weapon(t_gdata *data, char *path);
static int	get_weapon_texel(t_gdata *gd, int x, int y, int frame_offset);

int	set_weapon(t_gdata *gd)
{
	gd->weapon.model[0] = parse_weapon(gd, "textures/wolfenstein/rifle.xpm");
	gd->weapon.model[1] = parse_weapon(gd, "textures/wolfenstein/pistol.xpm");
	gd->weapon.model[2] = parse_weapon(gd, "textures/wolfenstein/knife.xpm");
	gd->weapon.model[3] = parse_weapon(gd, "textures/wolfenstein/minigun.xpm");
	if (!gd->weapon.model[0] || !gd->weapon.model[1] || !gd->weapon.model[2]
		|| !gd->weapon.model[3])
		return (1);
	return (0);
}

static int	*parse_weapon(t_gdata *gd, char *path)
{
	t_canvas	img;
	int			*array;
	int			x;
	int			y;

	init_img(&img);
	img.img = mlx_xpm_file_to_image(gd->mlx,
			path, &gd->weapon.width, &gd->weapon.height);
	if (img.img == NULL)
		return (ft_error("Failed to init mlx image!"), NULL);
	img.addr = (int *)mlx_get_data_addr(img.img,
			&img.bpp, &img.ll, &img.endian);
	array = ft_calloc(sizeof(int), gd->weapon.width * gd->weapon.height);
	y = -1;
	while (++y < gd->weapon.height)
	{
		x = -1;
		while (++x < gd->weapon.width)
		{
			array[x + y * gd->weapon.width] = img.addr[x + y
				* gd->weapon.width];
		}
	}
	return (mlx_destroy_image(gd->mlx, img.img), array);
}

void	draw_weapon(t_gdata *gd)
{
	int		frame_offset;
	int		x;
	int		y;
	int		colour;

	y = -1;
	frame_offset = gd->weapon.frame * (64 + 1);
	while (++y < 512)
	{
		x = -1;
		while (++x < 512)
		{
			colour = get_weapon_texel(gd, x, y, frame_offset);
			if (colour != 9961608)
				put_pixel(&gd->canvas, x + W_WIDTH / 4, y + W_HEIGHT - 512,
					colour);
		}
	}
}

static inline int	get_weapon_texel(t_gdata *gd, int x, int y,
		int frame_offset)
{
	int		src_x;
	int		src_y;
	int		colour;

	src_x = frame_offset + (x * 64) / 512;
	src_y = (y * 64) / 512;
	colour = gd->weapon.model[gd->weapon.current][src_x + src_y
		* gd->weapon.width];
	return (colour);
}
