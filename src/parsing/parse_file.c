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

static int	line_count(char *file);
static void	map_fill(char **map, int fd);

// grabs map data from file into char ** array gdata->map
int	parse_file(t_gdata *gdata, char *file)
{
	int		rows;
	(void) gdata;
	(void) file;

	rows = line_count(file);
	gdata->map = (char **) malloc(sizeof(char *) * (rows + 1));
	if (!gdata->map)
		return (ft_error("malloc failed"), 1);
	gdata->file_fd = open(file, O_RDONLY);
	if (gdata->file_fd < 0)
		ft_error(strerror(errno));
	map_fill(gdata->map, gdata->file_fd);
	return (0);
}

// gets number of lines in map file
static int line_count(char *file)
{
	int		fd;
	int		count;
	char	*buffer;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(strerror(errno));
	else
	 {
		buffer = get_next_line(fd);
		while (buffer)
		{
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

	row = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		map[row] = ft_strdup(buffer);
		if (!map[row])
			return (free(map), ft_error("malloc failed"));
		row++;
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
}
