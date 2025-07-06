/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_has_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:08:21 by abhi              #+#    #+#             */
/*   Updated: 2025/07/06 13:02:44 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		line_count(t_gdata *data, char *file);
static int		map_fill(t_gdata *gd, char **map, int fd);
static int		copy_buffer_error(t_gdata *gd, char *buffer, char **map, int row);
static bool		buffer_has_map_data(char *buffer, size_t buffer_len);
static size_t	map_line_trim_from_end(char *buffer, size_t buffer_len);
static void		map_update_width_if_wider(t_gdata *gd, char *buffer);

// grabs map data from file into char ** array gd->map
int	parse_file_has_error(t_gdata *gd, char *file_name)
{
	gd->map_height = line_count(gd, file_name);
	if (!gd->map_height)
		return (gd->exit_status = EINVMAPHEIGHT);
	gd->map = (char **) ft_calloc(sizeof(char *), gd->map_height + 1);
	if (!gd->map)
		return (perror("Error: Cub3D"), gd->exit_status = ENOMEM);
	gd->file_fd = open(file_name, O_RDONLY);
	if (gd->file_fd < 0)
		return (ft_error(strerror(errno)),
			free(gd->map), gd->exit_status = EFAILOPENFILE);
	return (map_fill(gd, gd->map, gd->file_fd));
}

// return: number of lines in map file
//
// also calculates and stores the biggest/longest line found
// into map_width, which is used to malloc each string in map array
static int	line_count(t_gdata *gd, char *file)
{
	int		fd;
	size_t	map_row_count;
	char	*buffer;

	map_row_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error: Cub3D"),
			gd->exit_status = EFAILOPENFILE, map_row_count);
	else
	{
		buffer = get_next_line(fd);
		while (buffer)
		{
			if (buffer_has_map_data(buffer, ft_strlen(buffer)))
			{
				map_update_width_if_wider(gd, buffer);
				map_row_count++;
			}
			free(buffer);
			buffer = get_next_line(fd);
		}
	}
	return (close_fd(&fd), gd->exit_status = EXIT_SUCCESS, map_row_count);
}

static void	map_update_width_if_wider(t_gdata *gd, char *buffer)
{
	size_t	map_col_count;

	map_col_count = ft_strlen(buffer);
	map_col_count = map_line_trim_from_end(buffer, map_col_count);
	if (map_col_count > (size_t)gd->map_width)
			gd->map_width = map_col_count;
}

static bool	buffer_has_map_data(char *buffer, size_t buffer_len)
{
	size_t	i;

	if (!buffer)
		return (0);
	i = 0;
	while (i < buffer_len)
	{
		if (!ft_strchr(MAP_ALLOWED_CHARS, buffer[i]))
			return (false);
		i++;
	}
	return (true);
}

// trim new lines '\n' and spaces ' ' starting from the end of the buffer,
// which contains map data
//
// return new size of trimmed buffer
static size_t	map_line_trim_from_end(char *buffer, size_t len)
{
	while (len > 1 && (buffer[len - 1] == '\n' || buffer[len - 1] == ' '))
	{
		buffer[len - 1] = '\0';
		len--;
	}
	return (ft_strlen(buffer));
}

// copy contents of map file into map array
// and sets gd->map_height to the count of rows
//
// first while loop checks for texture data, breaks once it hits the map
static int	map_fill(t_gdata *gd, char **map, int fd)
{
	char	*buffer;
	int		row;

	row = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (parse_texture_data(gd, buffer)) // TO-DO: how does this work? ALWAYS RETURNS 0 (zero)
			break ;
		free(buffer);
		buffer = get_next_line(fd);
	}
	while (buffer)
	{
		if (copy_buffer_error(gd, buffer, map, row))
		//if (!map[row])
			return (free_array(map), free(buffer),
				perror("Error: Cub3D"), gd->exit_status);
		row++;
		free(buffer);
		buffer = get_next_line(fd);
	}
	map[row] = NULL;
	gd->map_height = row;
	return (gd->exit_status = EXIT_SUCCESS);
}

// normalises each map line to have the same width
// empty gaps are represented by a ' ' sign
// actually, it doesn't need to be a dash, it can just be a
// space character. so once we no longer need to print the
// map with print_map_info, we can remove the while loop at the end
// and replace the ' ' checks with ' '
static int	copy_buffer_error(t_gdata *gd, char *buffer, char **map, int row)
{
	char	*nl_char;

	map[row] = (char *) malloc(sizeof(char *) * (gd->map_width + 1));
	if (!map[row])
		return (gd->exit_status = ENOMEM);
	ft_memset(map[row], ' ', gd->map_width);
	ft_memcpy(map[row], buffer, ft_strlen(buffer));
	map[row][gd->map_width] = '\0';
	nl_char = ft_strchr(map[row], '\n');
	if (nl_char)
		*nl_char = ' ';
	return (gd->exit_status = EXIT_SUCCESS);
}
