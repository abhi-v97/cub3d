/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-24 08:28:09 by abhi              #+#    #+#             */
/*   Updated: 2025-06-24 08:28:09 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texture_info(t_gdata *data, char *buffer);

// checks if a line isn't blank, then attempts to set texture data
int	parse_texture_data(t_gdata *data, char *buffer)
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

// checks if the string matches the correct specifier for a texture
static int	set_texture_info(t_gdata *data, char *buffer)
{
	if (ft_strchr("01", buffer[0]))
		return (1);
	else if (buffer[0] == 'N' && buffer[1] == 'O')
		set_textures(data, buffer + 2, NORTH);
	else if (buffer[0] == 'W' && buffer[1] == 'E')
		set_textures(data, buffer + 2, WEST);
	else if (buffer[0] == 'S' && buffer[1] == 'O')
		set_textures(data, buffer + 2, SOUTH);
	else if (buffer[0] == 'E' && buffer[1] == 'A')
		set_textures(data, buffer + 2, EAST);
	else if (buffer[0] == 'F' && buffer[1] == ' ')
		set_textures(data, buffer + 2, FLOOR);
	else if (buffer[0] == 'C' && buffer[1] == ' ')
		set_textures(data, buffer + 2, CEILING);
	else
		return (1);
	return (0);
}
