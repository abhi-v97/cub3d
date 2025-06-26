/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 08:28:09 by abhi              #+#    #+#             */
/*   Updated: 2025-06-24 08:28:09 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cub3d.h"

static int	set_texture_info(t_texture *t, char *buffer);
static char	*set_texture_path(char *buffer);
// static int	check_textures_valid(t_texture *t);

int	get_textures(t_gdata *data, char *buffer)
{
	int		i;

	i = 0;
	while (is_blank(buffer[i]))
		i++;
	if (!buffer[i] || buffer[i] == '\n')
		return (0);
	if (buffer[i] && buffer[i + 1])
		return (set_texture_info(data->texture, buffer + i));
	return (0);
}

static int	set_texture_info(t_texture *t, char *buffer)
{
	if (ft_strchr("01", buffer[0]))
		return (1);
	else if (buffer[0] == 'N' && buffer[1] == 'O')
		t->north = set_texture_path(buffer + 2);
	else if (buffer[0] == 'W' && buffer[1] == 'E')
		t->west = set_texture_path(buffer + 2);
	else if (buffer[0] == 'S' && buffer[1] == 'O')
		t->south = set_texture_path(buffer + 2);
	else if (buffer[0] == 'E' && buffer[1] == 'A')
		t->east = set_texture_path(buffer + 2);
	else if (buffer[0] == 'F' && buffer[1] == ' ')
		t->floor = set_texture_path(buffer + 2);
	else if (buffer[0] == 'C' && buffer[1] == ' ')
		t->ceiling = set_texture_path(buffer + 2);
	else
	 	return (1);
	return (0);
}

// this function copies path of texture file from buffer into result
// i: whitespace amount
// texture file specifier (NO, WE, etc) and the path itself
// len: length of the path plus whitespace
// ft_strndup(buffer + i, len - i - 1)
// buffer + i tells strndup to begin copying from where the whitespace ends
// len - i - 1: len - i to subtract the whitespace chars from len, and 
// another -1 to subtract the '/n' char from gnl
static char	*set_texture_path(char *buffer)
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

// static int	check_textures_valid(t_texture *t)
// {
// 	int		fd;
// 	int		i;

// 	if (!t->north || !t->west || !t->south || !t->east || !t->floor || !t->ceiling)
// 		return (ft_error("missing textures!"), 1);
// 	return (0);
// }
