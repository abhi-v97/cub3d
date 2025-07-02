/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_click_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:51:44 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 17:55:12 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	mouse_click_handler(int mbutt, int x, int y, void *gdata_ptr)
{
	t_gdata *gd;

	gd = (t_gdata *)gdata_ptr;
	(void) gd;
	(void) x;
	(void) y;
	if (mbutt == M_SCROLLUP)
	{
		//..
	}
	else if (mbutt == M_SCRODOWN)
	{
		//..
	}
	else if (mbutt == M_LEFTBUTT)
	{
		//..
	}
	else if (mbutt == M_RIGHTBUTT)
	{
		//..
	}
	else if (mbutt == M_MIDDLEBUTT)
	{
		//..
	}
	return (1);
}
