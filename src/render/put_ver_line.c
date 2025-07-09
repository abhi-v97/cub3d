/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ver_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:07:24 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:17:29 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_ver_line(t_canvas *canvas, int x, t_ray *ray, int color)
{
	int	y;

	y = ray->draw_start;
	while (y <= ray->draw_end)
		put_pixel(canvas, x, y++, color);
}
