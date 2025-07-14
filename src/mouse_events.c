/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:19:37 by aistok            #+#    #+#             */
/*   Updated: 2025/07/14 14:11:14 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	mouse_moving_right(t_gdata *gd)
{
	//t_ipos	mouse_current_pos;

	//mlx_mouse_get_pos(gd->mlx,
	//	gd->win, &mouse_current_pos.x, &mouse_current_pos.y);
	if (gd->mouse_prev_pos.x - gd->mouse_pos.x < 0)
	//if (gd->mouse_prev_pos.x - mouse_current_pos.x < 0)
		return (true);
	return (false);
}

bool	mouse_moving_left(t_gdata *gd)
{
	//t_ipos	mouse_current_pos;

	//mlx_mouse_get_pos(gd->mlx,
	//	gd->win, &mouse_current_pos.x, &mouse_current_pos.y);
	if (gd->mouse_prev_pos.x - gd->mouse_pos.x > 0)
	//if (gd->mouse_prev_pos.x - mouse_current_pos.x > 0)
		return (true);
	return (false);
}

void	mouse_update(t_gdata *gd)
{
	gd->mouse_prev_pos = gd->mouse_pos;
	mlx_mouse_get_pos(gd->mlx,
        gd->win, &gd->mouse_pos.x, &gd->mouse_pos.y);
	//mlx_mouse_move(gd->mlx, gd->win,
	//	gd->mouse_prev_pos.x, gd->mouse_prev_pos.y);
}
