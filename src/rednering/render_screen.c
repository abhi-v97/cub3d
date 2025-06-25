/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:34:50 by aistok            #+#    #+#             */
/*   Updated: 2025/06/25 14:45:01 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_screen(void *param)
{
	const t_gdata *const	gd = param;
	int						limit;
	int						*data;
	int						i;

	data = (int *)gd->cnvs.addr;
	limit = gd->cnvs.w * gd->cnvs.h;
	i = 0;
	while (i < limit)
		data[i++] = 0x000000ff;
	//ft_memset((void *)data, 0x0000FF00, limit * 4 - 12);
	// printf("Line %d\n", __LINE__);
	mlx_put_image_to_window(gd->display, gd->win, gd->cnvs.img, 0, 0);
	// printf("Line %d\n", __LINE__);
	usleep(100000);
	return (1);
}
