/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ver_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:07:24 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 18:10:16 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_ver_line(t_canvas *canvas, int x, int y1, int y2, int color)
{
	while (y1 <= y2)
		put_pixel(canvas, x, y1++, color);
}
