/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 10:46:48 by abhi              #+#    #+#             */
/*   Updated: 2025/07/13 23:25:17 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

static void	show_usage(char **argv);

// print error msg to stderr
void	ft_error(char *msg)
{
	char	*program_name;

	program_name = get_program_name();
	write(STDERR_FILENO, program_name, ft_strlen(program_name));
	write(STDERR_FILENO, ": Error: ", 9);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	ft_perror(void)
{
	char	*program_name;

	program_name = get_program_name();
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, program_name, ft_strlen(program_name));
	write(STDERR_FILENO, ": ", 2);
	perror(NULL);
}

int	handle_error(int return_code, char **argv)
{
	if (return_code == EINVARGS)
		show_usage(argv);
	else if (return_code == EFAILOPENFILE)
		ft_error("Failed to open file!");
	else if (return_code == EBADFILEEXT)
		ft_error("Wrong extension!");
	else if (return_code == ERR_MALLOC)
		ft_error("Malloc failed!");
	else if (return_code == EMLXINIT)
		ft_error("mlx failed to initialize!");
	else if (return_code == EMLXWINCREATE)
		ft_error("failed to initialize mlx window!");
	else if (return_code == EMLXIMGCREATE)
		ft_error("failed to initialize mlx image!");
	else if (return_code == EINVMAP)
		ft_error("invalid map!");
	else if (return_code == EMAPINVCHAR)
		ft_error("Invalid character found in map!");
	else if (return_code == E_INV_PLAYER)
		ft_error("Map has none or too many players!");
	else if (return_code == EMISSINGTEXTURE)
		ft_error("Missing texture!");
	return (return_code);
}

static void	show_usage(char **argv)
{
	ft_putstr_fd("Invalid args! \n\n", STDERR_FILENO);
	ft_putstr_fd("Usage: \n", STDERR_FILENO);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(" [map_file]\n", STDERR_FILENO);
}
