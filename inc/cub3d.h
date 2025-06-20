/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:25 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/20 18:47:50 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include "../minilibx-linux/mlx.h"

# define EMLXERR 1
# define EMLXWINERR 2

# define k_ESC 65307
# define k_left 65361
# define k_up 65362
# define k_right 65363
# define k_down 65364
# define k_lt 44
# define k_gt 46
# define k_sqb1 91
# define k_sqb2 93
# define k_a 97
# define k_c 99
# define k_l 108
# define k_d 100
# define k_r 114
# define k_s 115
# define k_w 119
# define k_x 120

/*
 *	bpp - bit per pixel
 *	ll	- line length
 */
typedef struct s_canvas
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}	t_canvas;

typedef struct s_gdata
{
	void		*display;
	void		*win;
	t_canvas	cnvs;
	int			ww;
	int			wh;
	int			exit_code;
}	t_gdata;

#endif