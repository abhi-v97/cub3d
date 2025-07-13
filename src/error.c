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

void	ft_errmsg(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
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
