/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:08:50 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 18:10:16 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_all(t_canvas *canvas, int color)
{
	int	x;
	int	y;

	x = -1;
	while (++x < canvas->w)
	{
		y = -1;
		while (++y < canvas->h)
			put_pixel(canvas, x, y, color);
	}
}
