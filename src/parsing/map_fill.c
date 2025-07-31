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

static int		copy_buffer_error(t_gdata *gd, char *buf, char **map, int row);
static int		missing_textures(t_gdata *gd);

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
		if (parse_texture_data(gd, buffer))
			break ;
		free(buffer);
		buffer = get_next_line(fd);
	}
	while (buffer)
	{
		if (copy_buffer_error(gd, buffer, map, row++))
			return (free(buffer), ft_perror(), gd->exit_status);
		free(buffer);
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
	gd->map_height = row;
	if (missing_textures(gd))
		return (gd->exit_status);
	return (exit_status(gd, EXIT_SUCCESS));
}

// normalises each map line to have the same width
// empty gaps are represented by a ' ' sign
// actually, it doesn't need to be a dash, it can just be a
// space character. so once we no longer need to print the
// map with print_map_info, we can remove the while loop at the end
// and replace the ' ' checks with ' '
static int	copy_buffer_error(t_gdata *gd, char *buf, char **map, int row)
{
	char	*nl_char;

	map[row] = (char *) malloc(sizeof(char *) * (gd->map_width + 1));
	if (!map[row])
		return (exit_status(gd, ENOMEM));
	ft_memset(map[row], ' ', gd->map_width);
	ft_memcpy(map[row], buf, ft_strlen(buf));
	map[row][gd->map_width] = '\0';
	nl_char = ft_strchr(map[row], '\n');
	if (nl_char)
		*nl_char = ' ';
	return (exit_status(gd, EXIT_SUCCESS));
}

// checks if each cardinal direction has a value in gd->textures or
// gd->tex_rgb, which are calloc'd and will be zero if not set by
// set_textures func
// Only checks NWSE for now
static int	missing_textures(t_gdata *gd)
{
	t_cardinal	dir;

	dir = 0;
	while (dir <= WEST)
	{
		if (!gd->textures[dir] && !gd->tex_rgb[dir])
			return (exit_status(gd, EMISSINGTEXTURE));
		dir++;
	}
	return (exit_status(gd, EXIT_SUCCESS));
}
