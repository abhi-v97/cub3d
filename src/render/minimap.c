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

int	set_colour(t_gdata *gd, int row, int col)
{
	int		colour;

	colour = 0;
	if (gd->map[row][col] == ' ')
		colour = 0xFF7F50; // orange door hinge
	else if (gd->map[row][col] == '0')
		colour = 0xFFBF00; // yellow marshmellow
	else if (gd->map[row][col] == '1')
		colour = 0xDE3163; // maroon lagoon
	else
		colour = 0x6495ED; // blue skies

	return (colour);

}

int	**minimap_colours(t_gdata *gd)
{
	int	**array;

	(void) gd;
	array = ft_calloc(sizeof(int *), gd->map_height + 1);
	if (array == NULL)
		return (NULL);
	for (int row = 0; row < gd->map_height; row++)
	{
		array[row] = ft_calloc(sizeof(int), gd->map_width + 1);
		for (int col = 0; col < gd->map_width; col++)
		{
			array[row][col] = set_colour(gd, row, col);
		}
	}
	return (array);
}

void	draw_block(t_gdata *gd, t_minimap minimap)
{
	
}