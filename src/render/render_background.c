/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:56:47 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:24:31 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_gdata *gd)
{
	draw_ceiling(&gd->canvas, gd->tex_rgb[CEILING]);
	draw_floor(&gd->canvas, gd->tex_rgb[FLOOR]);
}
