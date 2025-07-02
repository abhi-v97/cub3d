/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:19:50 by abhi              #+#    #+#             */
/*   Updated: 2025/06/30 18:10:16 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// prints map info from t_gdata struct
void	print_map_info(t_gdata *data)
{
	int		i;

	printf("map_height:\t\t%i\n", data->map_height);
	printf("map_width:\t\t%i\n", data->map_width);
	printf("\nMap:\n");
	i = 0;
	while (data->map[i])
		printf("\t%s\n", data->map[i++]);
}

// debug function
// used to test if all four textures are appearing on screen correctly
// offset is the x offset to prevent image overlap
void	test_textures(t_gdata *data, int *texture, int offset)
{
	int		*pixel_address;
	int		i;
	int		j;
	int		k;

	pixel_address = (int *)data->canvas.addr;
	k = 0;
	while (k < 256 * 256)
	{
		i = k % 256;
		j = k / 256;
		pixel_address[(i + offset) + (j * 1600)]
			= texture[i + j * data->tex_size];
		k++;
	}
}
