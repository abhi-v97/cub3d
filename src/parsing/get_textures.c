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

static int	set_texture_info(t_gdata *data, char *str);
static char	*set_texture_path(t_gdata *data, char *buffer);

int	get_textures(t_gdata *data, char *buffer)
{
	int		i;

	i = 0;
	while (is_blank(buffer[i]))
		i++;
	if (!buffer[i] || buffer[i] == '\n')
		return (0);
	if (buffer[i] && buffer[i + 1])
		return (set_texture_info(data, buffer + i));
	return (0);
}

static int	set_texture_info(t_gdata *data, char *buffer)
{
	(void) data;
	if (ft_strchr("01", buffer[0]))
		return (1);
	else if (buffer[0] == 'N' && buffer[1] == 'O')
		data->texture_n = set_texture_path(data, buffer + 2);
	else if (buffer[0] == 'W' && buffer[1] == 'E')
		data->texture_w = set_texture_path(data, buffer + 2);
	else if (buffer[0] == 'S' && buffer[1] == 'O')
		data->texture_s = set_texture_path(data, buffer + 2);
	else if (buffer[0] == 'E' && buffer[1] == 'A')
		data->texture_e = set_texture_path(data, buffer + 2);
	else if (buffer[0] == 'F' && buffer[1] == ' ')
		data->texture_f = set_texture_path(data, buffer + 2);
	else if (buffer[0] == 'C' && buffer[1] == ' ')
		data->texture_c = set_texture_path(data, buffer + 2);
	else
	 	return (1);
	return (0);
}

static char	*set_texture_path(t_gdata *data, char *buffer)
{
	int		i;
	int		len;
	char	*result;

	(void) data;
	i = 0;
	while (buffer[i] && is_blank(buffer[i]))
		i++;
	len = i;
	while (buffer[len] && !is_blank(buffer[len] && buffer[len] != '\n'))
		len++;
	result = (char *) malloc(sizeof(char) * (len - i));
	if (!result)
		return (NULL);
	result = ft_strndup(buffer + i, len - i - 1);
	return (result);
}
