/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhi <abhi@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 20:19:26 by abhi              #+#    #+#             */
/*   Updated: 2025-08-06 20:19:26 by abhi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sprite(t_gdata *gd, char *buffer)
{
	char	*path;

	path = get_texture_path(buffer);
	if (!path)
		return ;
	if (gd->num_sprite_tex < 4)
	{
		if (path && ft_strchr(path, '/'))
			gd->sprite_tex[gd->num_sprite_tex++] = parse_xpm(gd, path);
	}
	else 
		exit_status(gd, 31);
	free(path);
}

void	set_sprite_pos(t_gdata *gd, char *buffer)
{
	char	**deets;

	if (gd->num_sprite_pos > 3)
	{
		exit_status(gd, 31);
		return ;
	}
	deets = ft_split(buffer, ',');
	if (deets && deets[0] && deets[1] && deets[2])
	{
		gd->sprite[gd->num_sprite_pos].tex = ft_atoi(deets[0]);
		gd->sprite[gd->num_sprite_pos].x = ft_atoi(deets[1]) + 0.5;
		gd->sprite[gd->num_sprite_pos].y = ft_atoi(deets[2]) + 0.5;
	}
	else
		exit_status(gd, 31);
	gd->num_sprite_pos++;
	free_array((void **)deets);
}
