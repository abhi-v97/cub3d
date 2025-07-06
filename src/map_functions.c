/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 05:47:50 by aistok            #+#    #+#             */
/*   Updated: 2025/07/02 05:48:42 by aistok           ###   ########.fr       */
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
