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
