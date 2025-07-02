/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moving_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:21:39 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 21:47:06 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	mouse_moving_right(t_gdata *gd)
{
	t_ipos	mouse_current_pos;

	mlx_mouse_get_pos(gd->mlx, gd->win, &mouse_current_pos.x, &mouse_current_pos.y);
	mlx_mouse_move(gd->mlx, gd->win, gd->mpos_at_start.x, gd->mpos_at_start.y);
	if (gd->mpos_at_start.x - mouse_current_pos.x > 0)
	{
		return (true);
	}
	return (false);
}
