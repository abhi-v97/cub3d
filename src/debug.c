/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-27 14:19:50 by abhi              #+#    #+#             */
/*   Updated: 2025-06-27 14:19:50 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// prints map info from t_gdata struct
void	print_map_info(t_gdata *data)
{
	int		i;

	printf("map_height:\t\t%i\n", data->map_height);
	printf("map_width:\t\t%i\n", data->map_width);
	printf("\nTexture info:\n");
	printf("north:\t\t%s\n", data->texture_path->north);
	printf("south:\t\t%s\n", data->texture_path->south);
	printf("west:\t\t%s\n", data->texture_path->west);
	printf("east:\t\t%s\n", data->texture_path->east);
	printf("floor:\t\t%s\n", data->texture_path->floor);
	printf("ceil:\t\t%s\n", data->texture_path->ceiling);
	printf("\nMap:\n");
	i = 0;
	while (data->map[i])
		printf("\t%s\n", data->map[i++]);
}

// debug function
// used to test if all four textures are appearing on screen correctly
// offset is the x offset to prevent image overlap
void	test_textures(t_gdata *data, t_img *texture, int offset)
{
	int *pixel_address;
	int i, j, k;

	pixel_address = (int *)data->cnvs.addr;

	k = 0;
	while (k < 256 * 256)
	{
		i = k % 256;
		j = k / 256;
		pixel_address[(i + offset) + (j * 1600)] = texture->address[i + j * data->texture_path->size];
		k++;
	}
}
