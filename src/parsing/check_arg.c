/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:43:15 by abhi              #+#    #+#             */
/*   Updated: 2025/07/09 23:24:04 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

static int	is_dir(char *file_name);
static int	check_ext(char *file_name);

// tests the map given as arg if its valid or not
// zero if valid, 1 if not: this results in an exit statement
int	check_arg(t_gdata *gd, char *file_name)
{
	int		fd;

	if (is_dir(file_name))
		return (exit_status(gd, EFILEISDIR));
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (ft_error("Failed to open file!"),
			exit_status(gd, EFAILOPENFILE));
	if (failed(check_ext(file_name)))
		return (close(fd),
			ft_error("Wrong extension!"), exit_status(gd, EBADFILEEXT));
	return (close(fd), exit_status(gd, EXIT_SUCCESS));
}

// checks if file provided is a directory or not
// returns 1 if it is, 0 if its not
static int	is_dir(char *file_name)
{
	int		fd;

	fd = open(file_name, O_DIRECTORY);
	if (fd >= 0)
		return (close_fd(&fd), ft_error("File is a directory!"), EFILEISDIR);
	return (close_fd(&fd), EXIT_SUCCESS);
}

// checks if the file has .cub extension
static int	check_ext(char *file_name)
{
	char	*temp;

	temp = ft_strrchr(file_name, '.');
	if (!temp)
		return (EBADFILEEXT);
	if (ft_strcmp(temp, ".cub"))
		return (EBADFILEEXT);
	return (EXIT_SUCCESS);
}
