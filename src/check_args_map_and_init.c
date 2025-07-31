/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_map_and_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:01:35 by aistok            #+#    #+#             */
/*   Updated: 2025/07/13 23:02:43 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// is player_outside_map unneccessary? I was not able to make a map that 
// triggers that line of code, a previous error check flags it first
int	check_args_map_and_init(t_gdata *gd, int argc, char **argv)
{
	set_program_name(argv[0]);
	if (argc < 2)
		return (ft_error("Need a map!"),
			exit_status(gd, EINVARGS));
	if (argc > 2)
		return (ft_error("Too many arguments!"),
			exit_status(gd, EINVARGS));
	if (failed(check_arg(gd, argv[1])))
		return (gd->exit_status);
	if (failed(init_all(gd)))
		return (gd->exit_status);
	if (failed(parse_file(gd, argv[1])))
		return (cleanup(gd), gd->exit_status);
	if (failed(check_map(gd)))
		return (cleanup(gd), exit_status(gd, 1));
	if (set_player_pos(gd))
		return (exit_status(gd, EMAPPLAYEROUTOFBOUNDS));
	player_set_direction(gd);
	return (exit_status(gd, EXIT_SUCCESS));
}
