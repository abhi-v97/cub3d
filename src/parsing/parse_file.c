/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-21 20:08:21 by abhi              #+#    #+#             */
/*   Updated: 2025-06-21 20:08:21 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <fcntl.h>

static int	line_count(t_gdata *data, char *file);
static void	map_fill(char **map, int fd);

// grabs map data from file into char ** array gdata->map
int	parse_file(t_gdata *gdata, char *file)
{
	(void) gdata;
	(void) file;
	gdata->map_height = line_count(gdata, file);
	gdata->map = (char **) malloc(sizeof(char *) * (gdata->map_height + 1));
	if (!gdata->map)
		return (ft_error("malloc failed"), 1);
	gdata->file_fd = open(file, O_RDONLY);
	if (gdata->file_fd < 0)
		ft_error(strerror(errno));
	map_fill(gdata->map, gdata->file_fd);
	return (0);
}

// gets number of lines in map file
static int	line_count(t_gdata *data, char *file)
{
	int		fd;
	int		count;
	char	*buffer;
	int		buffer_len;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	else
	{
		buffer = get_next_line(fd);
		while (buffer)
		{
			buffer_len = ft_strlen(buffer);
			if (buffer_len > data->map_width)
				data->map_width = buffer_len;
			free(buffer);
			buffer = get_next_line(fd);
			count++;
		}
	}
	return (close(fd), count);
}

// copy contents of map file into map array
static void	map_fill(char **map, int fd)
{
	char	*buffer;
	int		row;
	char	*nl_char;

	row = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		nl_char = ft_strchr(buffer, '\n');
		if (nl_char)
			*nl_char = '\0';
		map[row] = ft_strdup(buffer);
		if (!map[row])
			return (free(map), ft_error("malloc failed"));
		row++;
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
}
