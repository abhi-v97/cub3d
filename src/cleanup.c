/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:27:15 by aistok            #+#    #+#             */
/*   Updated: 2025/06/25 14:30:30 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    cleanup(t_gdata *gdata)
{
	if (gdata->cnvs.img)
		mlx_destroy_image(gdata->display, gdata->cnvs.img);
	if (gdata->win)
		mlx_destroy_window(gdata->display, gdata->win);
	if (gdata->display)
	{
		mlx_destroy_display(gdata->display);
		free(gdata->display);
	}
}
