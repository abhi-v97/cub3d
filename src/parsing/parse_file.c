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

#include "cub3d.h"
#include <fcntl.h>

static int	line_count(t_gdata *data, char *file);
static void	map_fill(t_gdata *data, char **map, int fd);
static void	copy_buffer(t_gdata *data, char *buffer, char **map, int row);

// grabs map data from file into char ** array gdata->map
int	parse_file(t_gdata *gdata, char *file)
{
	gdata->map = (char **) malloc(sizeof(char *) * (line_count(gdata, file) + 1));
	if (!gdata->map)
		return (ft_error(strerror(errno)), 1);
	gdata->file_fd = open(file, O_RDONLY);
	if (gdata->file_fd < 0)
		ft_error(strerror(errno));
	map_fill(gdata, gdata->map, gdata->file_fd);
	return (0);
}

// gets number of lines in map file
// also calculates and stores the biggest line found as
// the map_width, which is used to malloc each string in map array
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
				data->map_width = buffer_len - 1;
			free(buffer);
			buffer = get_next_line(fd);
			count++;
		}
	}
	return (close_fd(&fd), count);
}

// copy contents of map file into map array
static void	map_fill(t_gdata *data, char **map, int fd)
{
	char	*buffer;
	int		row;

	row = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (parse_texture_data(data, buffer))
			break ;
		free(buffer);
		buffer = get_next_line(fd);
	}
	while (buffer)
	{
		copy_buffer(data, buffer, map, row);
		if (!map[row])
			return (free(map), ft_error(strerror(errno)));
		row++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
	data->map_height = row;
}

// normalises each map line to have the same width
// empty gaps are represented by a ' ' sign
// actually, it doesn't need to be a dash, it can just be a
// space character. so once we no longer need to print the
// map with print_map_info, we can remove the while loop at the end
// and replace the ' ' checks with ' '
static void	copy_buffer(t_gdata *data, char *buffer, char **map, int row)
{
	char	*nl_char;
	// int		i;

	map[row] = (char *) malloc(sizeof(char *) * (data->map_width + 1));
	if (!map[row])
		return ;
	ft_memset(map[row], ' ', data->map_width);
	ft_memcpy(map[row], buffer, ft_strlen(buffer));
	map[row][data->map_width] = '\0';
	nl_char = ft_strchr(map[row], '\n');
	if (nl_char)
		*nl_char = ' ';	
}
