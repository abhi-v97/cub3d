/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_in_args_map_or_init.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:01:35 by aistok            #+#    #+#             */
/*   Updated: 2025/07/06 12:46:54 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_error_in_args_map_or_init(t_gdata *gd, int argc, char **argv)
{
	if (argc < 2)
		return (ft_error("Need a map!"),
			gd->exit_status = EINVALARGCOUNT);
	if (argc > 2)
		return (ft_error("Too many parameters!"),
			gd->exit_status = EINVALARGCOUNT);
	if (check_arg(gd, argv[1]))
		return (gd->exit_status);
	if (init_gdata_has_error(gd))
		return (gd->exit_status);
	if (parse_file_has_error(gd, argv[1]))
		return (cleanup(gd), gd->exit_status);
	if (check_map_error(gd))
		return (cleanup(gd), gd->exit_status);
	gd->player.pos = player_get_pos_from_map(gd);
	player_set_direction(gd);
	if (gd->player.pos.x > 0 && gd->player.pos.y > 0
		&& player_outside_map(gd, gd->player.pos))
		return (ft_error("Player out of bounds!"),
			gd->exit_status = EMAPPLAYEROUTOFBOUNDS);
	return (gd->exit_status = EXIT_SUCCESS);
}
