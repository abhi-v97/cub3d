/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-27 16:48:18 by abhi              #+#    #+#             */
/*   Updated: 2025-06-27 16:48:18 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		*parse_xpm(t_gdata *data, char *path);
static void		init_img(t_img *img);
static char		*get_texture_path(char *buffer);
static int		set_rgb(char *path);

void	set_textures(t_gdata *data, char *buffer, t_cardinal wall_dir)
{
	char	*path;

	path = get_texture_path(buffer);
	if (path && ft_strchr(path, '/'))
		data->textures[wall_dir] = parse_xpm(data, path);
	else if (path && (path[0] >= '0' && path[0] <= '9'))
		data->tex_rgb[wall_dir] = set_rgb(path);
	free(path);
}

static int	*parse_xpm(t_gdata *data, char *path)
{
	t_img	img;
	int		*array;
	int		i;
	int		x;
	int		y;

	init_img(&img);
	img.img = mlx_xpm_file_to_image(data->mlx,
			path, &data->tex_size, &data->tex_size);
	if (img.img == NULL)
		(ft_error("missing texture"), exit(1));
	img.address = (int *)mlx_get_data_addr(img.img,
			&img.pixel_bits, &img.size, &img.endian);
	array = ft_calloc(sizeof(int), data->tex_size * data->tex_size);
	i = 0;
	while (i < data->tex_size * data->tex_size)
	{
		x = i % data->tex_size;
		y = i / data->tex_size;
		array[x + y * data->tex_size] = img.address[x + y * data->tex_size];
		i++;
	}
	mlx_destroy_image(data->mlx, img.img);
	return (array);
}

static void	init_img(t_img *img)
{
	img->img = NULL;
	img->address = NULL;
	img->pixel_bits = 0;
	img->size = 0;
	img->endian = 0;
}

// this function copies path of texture file from buffer into result
// i: whitespace amount
// texture file specifier (NO, WE, etc) and the path itself
// len: length of the path plus whitespace
// ft_strndup(buffer + i, len - i - 1)
// buffer + i tells strndup to begin copying from where the whitespace ends
// len - i - 1: len - i to subtract the whitespace chars from len, and 
// another -1 to subtract the '/n' char from gnl
static char	*get_texture_path(char *buffer)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	while (buffer[i] && is_blank(buffer[i]))
		i++;
	len = i;
	while (buffer[len] && !is_blank(buffer[len] && buffer[len] != '\n'))
		len++;
	result = ft_strndup(buffer + i, len - i - 1);
	if (!result)
		return (NULL);
	return (result);
}

static int	set_rgb(char *path)
{
	char	**array;
	int		r;
	int		g;
	int		b;
	int		i;

	r = 0;
	g = 0;
	b = 0;
	array = ft_split(path, ',');
	if (!array)
		return (r + (g << 8) + (b << 16));
	if (array[0])
		r = ft_atoi(array[0]);
	if (array[1])
		g = ft_atoi(array[1]);
	if (array[2])
		b = ft_atoi(array[2]);
	i = 0;
	while (array && array[i])
		free(array[i++]);
	free(array);
	return ((r << 16) + (g << 8) + b);
}
