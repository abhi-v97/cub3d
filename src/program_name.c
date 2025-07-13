/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 22:45:50 by aistok            #+#    #+#             */
/*   Updated: 2025/07/13 22:57:02 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*get_program_name();
void		set_program_name(char *program_name);
static char	*internal_program_name(char *program_name, t_action action);

void	set_program_name(char *program_name)
{
	internal_program_name(program_name, SET);
}

char	*get_program_name()
{
	return (internal_program_name(NULL, GET));
}

static char	*internal_program_name(char *program_name, t_action action)
{
	static char *int_program_name = NULL;

	if (action == SET)
		int_program_name = program_name;
	else if (action == GET)
		return (int_program_name);
	return (int_program_name);
}
