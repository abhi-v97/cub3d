/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-27 14:50:39 by abhi              #+#    #+#             */
/*   Updated: 2025-07-27 14:50:39 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*parse_weapon(t_gdata *data, char *path);

int	set_weapon(t_gdata *gd, char *buffer)
{
	char	*path;

	path = get_texture_path(buffer);
	if (!path || !path[0])
		return (1);
	gd->weapon = parse_weapon(gd, path);
	if (!gd->weapon)
		return (1);
	return (0);
}

int	*parse_weapon(t_gdata *data, char *path)
{
	t_canvas	img;
	int			*array;
	int			x;
	int			y;



	(void) path;
	init_img(&img);
	img.img = mlx_xpm_file_to_image(data->mlx,
			path, &data->weapon_width, &data->weapon_height);
	if (img.img == NULL)
		return (ft_error("Failed to init mlx image!"), NULL);
	img.addr = (int *)mlx_get_data_addr(img.img,
			&img.bpp, &img.ll, &img.endian);
	array = ft_calloc(sizeof(int), data->weapon_width * data->weapon_height);
	y = 0;
	while (y < data->weapon_height)
	{
		x = 0;
		while (x < data->weapon_width)
		{
			array[x + y * data->weapon_width] = img.addr[x + y * data->weapon_width];
			x++;
		}
		y++;
	}
	return (mlx_destroy_image(data->mlx, img.img), array);	
}

void	draw_weapon(t_gdata *gd)
{
	int frame_offset = gd->weapon_frame * (64 + 1);
	int src_x, src_y;
	
	int x = 0;
	int y = 0;
	while (y < 512)
	{
		x = 0;
		while (x < 512)
		{
			src_x = frame_offset + (x * 64) / 512;
			src_y = (y * 64) / 512;
			int color = gd->weapon[src_x + src_y * gd->weapon_width];
			if (color != 9961608)
				put_pixel(&gd->canvas, x + W_WIDTH / 4, y + W_HEIGHT - 512, color);
			x++;
		}
		y++;
	}
}
