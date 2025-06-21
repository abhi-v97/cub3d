/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-21 10:43:15 by abhi              #+#    #+#             */
/*   Updated: 2025-06-21 10:43:15 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
#include <fcntl.h>

static int	is_dir(char *file);
static int	check_ext(char *file);

// tests the map given as arg if its valid or not
// zero if valid, 1 if not: this results in an exit statement
int check_map(char *file)
{
	int		fd;

	if (is_dir(file))
		return (ft_error("File is a directory"), 1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (close(fd), ft_error("Failed to open file"), 1);
	if (check_ext(file))
		return (close(fd), ft_error("Wrong extension"), 1);
	return (0);
}

// checks if file provided is a directory or not
// returns 1 if it is, 0 if its not
static int	is_dir(char *file)
{
	int		fd;
	
	fd = open(file, O_DIRECTORY);
	if (fd >= 0)
		return (close(fd), 1);
	return (close(fd), 0);
}

// checks if the file has .cub extension
static int	check_ext(char *file)
{
	char	*temp;

	temp = ft_strrchr(file, '.');
	if (!temp && ft_strcmp(temp,	".cub"))
		return (1);
	return (0);
}
