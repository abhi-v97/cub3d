/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:57:22 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 21:57:41 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_canvas *canvas, int color)
{
	int	x;
	int	y;
	int	height_half;

	x = -1;
	height_half = canvas->h / 2;
	while (++x < canvas->w)
	{
		y = height_half;
		while (++y < canvas->h)
			put_pixel(canvas, x, y, color);
	}
}
