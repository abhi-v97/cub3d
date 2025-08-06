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

static void	draw_block(t_gdata *gd, int x_offset, int y_offset, int colour);
static int	set_colour(t_gdata *gd, int row, int col);
static int	fetch_colour(t_gdata *gd, int x, int y);

void	render_minimap(t_gdata *gd)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < 9)
	{
		while (y < 5)
		{
			get_pixel(&gd->canvas, x * 20, y * 20);
			draw_block(gd, x * 20, y * 20, fetch_colour(gd, x, y));
			y++;
		}
		x++;
		y = 0;
	}
}

int	**minimap_colours(t_gdata *gd)
{
	int	**array;
	int	row;
	int	col;

	array = ft_calloc(sizeof(int *), gd->map_height + 1);
	if (array == NULL)
		return (NULL);
	row = 0;
	while (row < gd->map_height)
	{
		array[row] = ft_calloc(sizeof(int), gd->map_width + 1);
		col = 0;
		while (col < gd->map_width)
		{
			array[row][col] = set_colour(gd, row, col);
			col++;
		}
		row++;
	}
	return (array);
}

static int	set_colour(t_gdata *gd, int row, int col)
{
	int		colour;

	colour = 0;
	if (ft_strchr("NSWE0", gd->map[row][col]))
		colour = 0xD7D7D7;
	else if (gd->map[row][col] == '1')
		colour = 0xFE7743;
	else
		colour = 0x273F4F;
	return (colour);
}

static int	fetch_colour(t_gdata *gd, int x, int y)
{
	int		colour;
	int		arr_x;
	int		arr_y;

	colour = 0x273F4F;
	if (x == 4 && y == 2)
		return (0x69B41E);
	arr_x = (int)gd->player.pos.x + x - 4;
	arr_y = (int)gd->player.pos.y + y - 2;
	if (arr_x >= 0 && arr_x < gd->map_width
		&& arr_y >= 0 && arr_y < gd->map_height)
		colour = gd->minimap.colour_array[arr_y][arr_x];
	return (colour);
}

// 400: minimap size squared, 20 * 20
// change to a macro or precalculate it to save performance
// function that draws one square block on the minimap, where one square block
// corresponds to one char on map file
static void	draw_block(t_gdata *gd, int x_offset, int y_offset, int colour)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	while (i < 400)
	{
		x = i % 20 + 20;
		y = i / 20 + 20;
		put_pixel(&gd->canvas, x + x_offset, y + y_offset, blend(colour,
				get_pixel(&gd->canvas, x + x_offset, y + y_offset), 128));
		i++;
	}
}
