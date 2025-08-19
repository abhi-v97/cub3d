/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:50:02 by abhi              #+#    #+#             */
/*   Updated: 2025/07/09 21:15:48 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// returns 1 if char is empty space
int	is_blank(char c)
{
	if (c == ' ' || (c <= '\r' && c >= '\t'))
		return (1);
	return (0);
}

// wrapper func to safely close a fd and set fd value to -1
void	close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// use this function to handle return codes
int	exit_status(t_gdata *data, int exit_code)
{
	data->exit_status = exit_code;
	return (exit_code);
}

// to make overall code more readable, this function
// can be used to check if a given function has failed
int	failed(int return_value)
{
	return (return_value != EXIT_SUCCESS);
}
