/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 16:14:36 by abhi              #+#    #+#             */
/*   Updated: 2025-08-06 16:14:36 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	weapon_fire(t_gdata *gd);

int	mouse_click(int button, int x, int y, t_gdata *gd)
{
	(void) x;
	(void) y;
	if (button == 1)
		weapon_fire(gd);
	return (0);
}

int	mouse_release(int button, int x, int y, t_gdata *gd)
{
	(void) x;
	(void) y;
	if (button == 1)
		gd->weapon.auto_fire = 0;
	return (0);
}

static void	weapon_fire(t_gdata *gd)
{
	if (gd->weapon.state == 0)
	{
		gd->weapon.state = 1;
		gd->weapon.frame = 1;
		if (gd->weapon.current == 0 || gd->weapon.current == 3)
			gd->weapon.auto_fire = 1;
	}
}
