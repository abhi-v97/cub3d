/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:08:21 by abhi              #+#    #+#             */
/*   Updated: 2025/08/16 14:06:45 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		line_count(t_gdata *data, char *file);
static void		update_map_width(t_gdata *gd, char *buffer);

// grabs map data from file into char ** array gd->map
// NOTE: will free everything, no need for cleanup outside for parse_file
int	parse_file(t_gdata *gd, char *file_name)
{
	if (failed(init_map_data(gd)))
		return (gd->exit_status);
	gd->map_height = line_count(gd, file_name);
	if (gd->map_height < 2 || gd->map_width < 2)
		return (exit_status(gd, EINVMAP));
	gd->map = (char **) ft_calloc(sizeof(char *), gd->map_height + 1);
	if (!gd->map)
		return (exit_status(gd, ERR_MALLOC));
	gd->file_fd = open(file_name, O_RDONLY);
	if (gd->file_fd < 0)
		return (exit_status(gd, EFAILOPENFILE));
	if (failed(map_fill(gd, gd->map, gd->file_fd)))
		return (close_fd(&gd->file_fd), gd->exit_status);
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
		return (exit_status(gd, EFAILOPENFILE), map_row_count);
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

// updates gd->map_width to that of the widest part of map,
// only if len of current buffer is greater
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
// skip over empty spaces. If the character is NSWEFC and the following
// character is not 0 or 1, its most likely a texture file
// if the texture file check is passed, it simply searches for a 0 or 1
// and returns true if it finds one
bool	buffer_has_map_data(char *buffer)
{
	int		i;
	if (!buffer)
		return (false);

	i = 0;
	while (buffer[i] == ' ')
		i++;
	if (ft_strchr("NSWEFC", buffer[i]) && !ft_strchr("01", buffer[i + 1]))
		return (false);
	if (ft_strchr(buffer, '0') || ft_strchr(buffer, '1'))
		return (true);
	else
		return (false);
}
