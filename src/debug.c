/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:19:50 by abhi              #+#    #+#             */
/*   Updated: 2025/08/05 18:46:39 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	debug_show_vars_after_init(t_gdata *gd)
{
	printf("Player X = %f, Y = %f\n",
		gd->player.pos.x, gd->player.pos.y);
}

// hooked to the P key, use it to print any var in data struct
void	debug_print(t_gdata *data)
{
	printf("dir x =%f\n", data->dir.x);
	printf("dir y =%f\n", data->dir.y);
}
