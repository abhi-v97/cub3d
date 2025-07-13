/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:08:21 by abhi              #+#    #+#             */
/*   Updated: 2025/07/13 23:22:53 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		line_count(t_gdata *data, char *file);

static bool		buffer_has_map_data(char *buffer);
static void		update_map_width(t_gdata *gd, char *buffer);

// grabs map data from file into char ** array gd->map
// NOTE: will free everything, no need for cleanup outside for parse_file
int	parse_file(t_gdata *gd, char *file_name)
{
	gd->map_height = line_count(gd, file_name);
	if (!gd->map_height || !gd->map_width)
		return (exit_status(gd, EINVMAPHEIGHT));
	gd->map = (char **) ft_calloc(sizeof(char *), gd->map_height + 1);
	if (!gd->map)
		return (ft_perror(), exit_status(gd, ENOMEM)); //cub3D executable name?
	gd->file_fd = open(file_name, O_RDONLY);
	if (gd->file_fd < 0)
		return (ft_error(strerror(errno)),
			free(gd->map), exit_status(gd, EFAILOPENFILE)); //since free(gd->map), there was a cleanup(gd) which attempted to free(map) the second time and that caused a segfault; now, there is no more cleanup(gd) outside, since this function handles all the freein?
	if (failed(map_fill(gd, gd->map, gd->file_fd)))
		return (close_fd(&gd->file_fd), free_array(gd->map),
			gd->exit_status);
	return (EXIT_SUCCESS);
}

// return: number of lines the map has (map height) in the .cub file
// also calculates and stores the biggest/longest map data line found
// into map_width, which is used to malloc each string in map array
static int	line_count(t_gdata *gd, char *file)
{
	int		fd;
	size_t	map_row_count;
	char	*buffer;

	map_row_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_perror(),
			exit_status(gd, EFAILOPENFILE), map_row_count);
	else
	{
		buffer = get_next_line(fd);
		while (buffer)
		{
			if (buffer_has_map_data(buffer))
			{
				update_map_width(gd, buffer);
				map_row_count++;
			}
			free(buffer);
			buffer = get_next_line(fd);
		}
	}
	return (close_fd(&fd), exit_status(gd, EXIT_SUCCESS), map_row_count);
}

// used to set gd->map_width to that of the widest part of map
// updates gd->map_width if len of current buffer is greater
static void	update_map_width(t_gdata *gd, char *buffer)
{
	size_t	len;

	len = ft_strlen(buffer);
	while (len > 1 && (buffer[len - 1] == '\n' || buffer[len - 1] == ' '))
	{
		buffer[len - 1] = '\0';
		len--;
	}
	if (len > (size_t)gd->map_width)
		gd->map_width = len;
}

// checks if map is a valid map line, used for the size of gd->map
// ***
// LOGIC: skip over blank space characters. If the next character is a 0 or 1
// (could just check for 1), it is considered a valid map file
// if its a texture line, first char after skipping space will be N or S etc
static bool	buffer_has_map_data(char *buffer)
{
	size_t	i;

	if (!buffer)
		return (false);
	i = 0;
	while (buffer[i] && buffer[i] == ' ')
		i++;
	if (buffer[i] && ft_strchr("01", buffer[i]))
		return (true);
	else
		return (false);
}
