/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:19:27 by abhi              #+#    #+#             */
/*   Updated: 2025/07/13 23:23:15 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		set_map_row(t_gdata *gd, char *buf, char **map, int *row);
static int		check_textures(t_gdata *gd);

// copy contents of map file into map array
// updates gd->map_height to total count of rows
// first while loop checks for texture data, breaks once it hits the map
int	map_fill(t_gdata *gd, char **map, int fd)
{
	char	*buffer;
	int		row;

	row = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (parse_textures(gd, buffer))
			break ;
		free(buffer);
		buffer = get_next_line(fd);
	}
	while (buffer)
	{
		if (set_map_row(gd, buffer, map, &row))
			gd->exit_status = EINVMAP;
		free(buffer);
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
	gd->map_height = row;
	return (check_textures(gd));
}

// normalises each map line to have the same width
// empty gaps are represented by a ' ' sign
static int	set_map_row(t_gdata *gd, char *buf, char **map, int *row)
{
	char	*nl_char;
	if (buffer_has_map_data(buf) == false)
		return (EXIT_FAILURE);
	map[*row] = (char *) malloc(sizeof(char *) * (gd->map_width + 1));
	if (!map[*row])
		return (exit_status(gd, ERR_MALLOC));
	ft_memset(map[*row], ' ', gd->map_width);
	ft_memcpy(map[*row], buf, ft_strlen(buf));
	map[*row][gd->map_width] = '\0';
	nl_char = ft_strchr(map[*row], '\n');
	if (nl_char)
		*nl_char = ' ';
	(*row)++;
	return (EXIT_SUCCESS);
}

// checks if each cardinal direction has a value in gd->textures or
// gd->tex_rgb, which are calloc'd and will be zero if not set by
// set_textures func
// Only checks NWSE for now, if floor or ceiling aren't set it defaults to
// black
// doesn't bother checking if gd->exit_status isn't zero
static int	check_textures(t_gdata *gd)
{
	t_cardinal	dir;

	if (gd->exit_status)
		return (gd->exit_status);
	dir = 0;
	while (dir <= WEST)
	{
		if (!gd->textures[dir] && !gd->tex_rgb[dir])
			return (exit_status(gd, EMAPTEXERROR));
		dir++;
	}
	return (EXIT_SUCCESS);
}
