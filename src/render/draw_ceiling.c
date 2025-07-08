/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:58:06 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 21:58:26 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling(t_canvas *canvas, int color)
{
	int	x;
	int	y;
	int	height_half;

	x = -1;
	height_half = canvas->h / 2;
	while (++x < canvas->w)
	{
		y = -1;
		while (++y <= height_half)
			put_pixel(canvas, x, y, color);
	}
}
