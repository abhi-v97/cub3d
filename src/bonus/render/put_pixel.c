/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:55:28 by aistok            #+#    #+#             */
/*   Updated: 2025/07/05 19:18:41 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_canvas *canvas, int x, int y, int color)
{
	char	*dst;

	dst = (char *)canvas->addr + (y * canvas->ll + x * (canvas->bpp / 8));
	*(unsigned int *)dst = color;
}

// alpha: 0 (fully bg) to 255 (fully fg)
int	blend(int fg, int bg, int alpha)
{
	int		r;
	int		g;
	int		b;

	r = ((fg >> 16) & 0xFF) * alpha / 255 + ((bg >> 16) & 0xFF) * (255 - alpha)
		/ 255;
	g = ((fg >> 8) & 0xFF) * alpha / 255 + ((bg >> 8) & 0xFF) * (255 - alpha)
		/ 255;
	b = (fg & 0xFF) * alpha / 255 + (bg & 0xFF) * (255 - alpha) / 255;
	return ((r << 16) | (g << 8) | b);
}

int	get_pixel(t_canvas *canvas, int x, int y)
{
	char	*dst;

	dst = (char *)canvas->addr + (y * canvas->ll + x * (canvas->bpp / 8));
	return (*(unsigned int *)dst);
}
