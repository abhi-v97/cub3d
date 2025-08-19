/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 16:23:25 by abhi              #+#    #+#             */
/*   Updated: 2025-08-06 16:23:25 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	weapon_switch(t_gdata *gd, int key)
{
	if ((key - XK_1) != gd->weapon.current)
	{
		gd->weapon.current = key - XK_1;
		gd->weapon.state = -1;
	}
	if (gd->weapon.state == -1)
	{
		gd->weapon.state = 2;
		gd->weapon.frame = 0;
	}
	else if (gd->weapon.state == 0)
	{
		gd->weapon.state = 3;
		gd->weapon.frame = 0;
	}
}

void	modify_pitch(t_gdata *gd, double move_speed)
{
	if (gd->keys[KEY_PITCH_DOWN])
	{
		gd->pitch -= 400 * move_speed;
		if (gd->pitch < -200)
			gd->pitch = -200;
	}
	if (gd->keys[KEY_PITCH_UP])
	{
		gd->pitch += 400 * move_speed;
		if (gd->pitch > 200)
			gd->pitch = 200;
	}
}

int	wall_status(t_gdata *gd, int x, int y)
{
	int		i;

	i = 0;
	while (i < gd->num_doors)
	{
		if (gd->door[i].x == x && gd->door[i].y == y)
			return (gd->door[i].status);
		i++;
	}
	return (1);
}
