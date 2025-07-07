/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-07 13:08:58 by avalsang          #+#    #+#             */
/*   Updated: 2025-07-07 13:08:58 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	minimap_colours(t_gdata *gd)
{
	gd->minimap.colour_array = ft_calloc(sizeof(char *), gd->map_height + 1);
	if (gd->minimap.colour_array == NULL)
		return ;
	
	for (int row = 0; row < gd->map_height; row++)
	{
		for (int col = 0; col < gd->map_width; col++)
		{
			;
		}
	}

}