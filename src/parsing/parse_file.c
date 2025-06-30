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

static int	line_count(t_gdata *data, char *file);
static int	map_fill(t_gdata *data, char **map, int fd);
static void	copy_buffer(t_gdata *data, char *buffer, char **map, int row);

// grabs map data from file into char ** array gdata->map
int	parse_file(t_gdata *gdata, char *file)
{
	gdata->map_height = line_count(gdata, file);
	if (!gdata->map_height)
		return (1);
	gdata->map = (char **) ft_calloc(sizeof(char *), gdata->map_height + 1);
	if (!gdata->map)
		return (perror("Error: Cub3d"), 1);
	gdata->file_fd = open(file, O_RDONLY);
	if (gdata->file_fd < 0)
		ft_error(strerror(errno));
	return (map_fill(gdata, gdata->map, gdata->file_fd));
}

// gets number of lines in map file
// also calculates and stores the biggest line found as
// the map_width, which is used to malloc each string in map array
static int	line_count(t_gdata *data, char *file)
{
	int		fd;
	int		count;
	char	*buffer;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error: Cub3d"), 0);
	else
	{
		buffer = get_next_line(fd);
		while (buffer)
		{
			if (ft_strchr(buffer, '1') || ft_strchr(buffer, '0'))
			{
				if ((int)ft_strlen(buffer) > data->map_width)
					data->map_width = ft_strlen(buffer) - 1;
				count++;
			}
			free(buffer);
			buffer = get_next_line(fd);
		}
	}
	return (close_fd(&fd), count);
}

// copy contents of map file into map array
// first while loop checks for texture data, breaks once it hits the map
static int	map_fill(t_gdata *data, char **map, int fd)
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
			return (free_array(map), free(buffer), perror("Error: Cub3d"), 1);
		row++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
	data->map_height = row;
	return (0);
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
