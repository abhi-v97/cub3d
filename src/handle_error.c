/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 23:05:07 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 23:35:32 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_error(int return_code, int argc, char **argv)
{
	if (return_code == EINVARGS)
		show_usage(argc, argv);
	else if (return_code == ENOMEM)
		ft_error("out of memory!");
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
	return (return_code);
}
