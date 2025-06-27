/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-27 12:56:24 by abhi              #+#    #+#             */
/*   Updated: 2025-06-27 12:56:24 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		init_img(t_img *img);
static t_img	*parse_xpm(t_gdata *data, char *path);

// prelim textures setup; need error checking
void	load_textures(t_gdata *data)
{
	data->t_north = parse_xpm(data, data->texture_path->north);
	data->t_west = parse_xpm(data, data->texture_path->west);
	data->t_south = parse_xpm(data, data->texture_path->south);
	data->t_east = parse_xpm(data, data->texture_path->east);
}

static void	init_img(t_img *img)
{
	img->img = NULL;
	img->address = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

static t_img	*parse_xpm(t_gdata *data, char *path)
{
	t_img	*img;

	img = (t_img *) malloc(sizeof(t_img));
	init_img(img);
	img->img = mlx_xpm_file_to_image(data->mlx, path, &data->texture_path->size, &data->texture_path->size);
	if (img->img == NULL)
		ft_error("missing texture"), exit(1);
	img->address = (int *)mlx_get_data_addr(img->img, &img->pixel_bits, &img->size_line, &img->endian);
	return (img);
}
