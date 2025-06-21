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

# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
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
	char		**map;
	int			file_fd;
	void		*win;
	t_canvas	cnvs;
	int			ww;
	int			wh;
	int			exit_code;
}	t_gdata;

// libft funcs
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);

// parsing/check_map.c
int		check_arg(char *file);

// parsing/parse_file.c
int		parse_file(t_gdata *gdata, char *file);

// error.c
void	ft_error(char *msg);

#endif
