/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 05:47:50 by aistok            #+#    #+#             */
/*   Updated: 2025/08/05 18:55:16 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	map_get(t_gdata *gd, int x, int y)
{
	return (gd->map[y][x]);
}

void	map_set(t_gdata *gd, int x, int y, char c)
{
	gd->map[y][x] = c;
}

t_ipos	pos_dtoi(t_pos dpos)
{
	return ((t_ipos){(int)dpos.x, (int)dpos.y});
}
