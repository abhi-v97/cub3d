/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:55:28 by aistok            #+#    #+#             */
/*   Updated: 2025/06/25 13:55:54 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_canvas *cdata, int x, int y, int color)
{
	char	*dst;

	dst = cdata->addr + (y * cdata->ll + x * (cdata->bpp / 8));
	*(unsigned int *)dst = color;
}
