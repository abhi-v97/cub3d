/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 19:03:30 by abhi              #+#    #+#             */
/*   Updated: 2025-08-06 19:03:30 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	weapon_shoot(t_gdata *gd)
{
	static int		old_time;

	if (!old_time)
		old_time = gd->time;
	if (gd->weapon.state == 1)
	{
		if (gd->time - old_time > 50000)
		{
			gd->weapon.frame++;
			old_time = gd->time;
		}
		if (gd->weapon.frame == 5)
		{
			if (gd->weapon.auto_fire)
			{
				gd->weapon.frame = 1;
				return ;
			}
			gd->weapon.state = 0;
			gd->weapon.frame = 0;
		}
	}
}

void	weapon_holster(t_gdata *gd)
{
	static int		old_time;

	if (!old_time)
		old_time = gd->time;
	if (gd->time - old_time > 100000)
	{
		gd->weapon.frame++;
		old_time = gd->time;
	}
	if (gd->weapon.frame == 1)
	{
		gd->weapon.state = -1;
		gd->weapon.frame = 0;
	}
}

void	weapon_equip(t_gdata *gd)
{
	static int		old_time;

	if (!old_time)
		old_time = gd->time;
	if (gd->time - old_time > 50000)
	{
		gd->weapon.frame++;
		old_time = gd->time;
	}
	if (gd->weapon.frame == 2)
	{
		gd->weapon.state = 0;
		gd->weapon.frame = 0;
	}
}

void	weapon_animate(t_gdata *gd)
{
	if (gd->weapon.state == -1)
		return ;
	draw_weapon(gd);
	if (gd->weapon.state == 1)
		weapon_shoot(gd);
	if (gd->weapon.state == 2)
		weapon_equip(gd);
	if (gd->weapon.state == 3)
		weapon_holster(gd);
}
