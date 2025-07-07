/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:28:09 by abhi              #+#    #+#             */
/*   Updated: 2025/07/07 23:39:42 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texture_info(t_gdata *gd, char *buffer);

// checks if a line isn't blank, then attempts to set texture data
int	parse_texture_data(t_gdata *gd, char *buffer)
{
	int		i;

	i = 0;
	while (is_blank(buffer[i]))
		i++;
	if (!buffer[i] || buffer[i] == '\n')
		return (exit_status(gd, EXIT_SUCCESS));
	if (buffer[i] && buffer[i + 1])
		return (set_texture_info(gd, buffer + i));
	return (exit_status(gd, EXIT_SUCCESS));
}

// checks if the string matches the correct specifier for a texture
static int	set_texture_info(t_gdata *gd, char *buffer)
{
	if (ft_strchr("01", buffer[0]))
		return (exit_status(gd, EMAPTEXINVALIDFILENAME));
	else if (buffer[0] == 'N' && buffer[1] == 'O')
		return (set_textures(gd, buffer + 2, NORTH), 0);
	else if (buffer[0] == 'W' && buffer[1] == 'E')
		return (set_textures(gd, buffer + 2, WEST), 0);
	else if (buffer[0] == 'S' && buffer[1] == 'O')
		return (set_textures(gd, buffer + 2, SOUTH), 0);
	else if (buffer[0] == 'E' && buffer[1] == 'A')
		return (set_textures(gd, buffer + 2, EAST), 0);
	else if (buffer[0] == 'F' && buffer[1] == ' ')
		return (set_textures(gd, buffer + 2, FLOOR), 0);
	else if (buffer[0] == 'C' && buffer[1] == ' ')
		return (set_textures(gd, buffer + 2, CEILING), 0);
	else
		return (exit_status(gd, EMAPTEXERROR));
}
