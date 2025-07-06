/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:25 by avalsang          #+#    #+#             */
/*   Updated: 2025/07/06 12:58:55 by aistok           ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"

# ifndef W_WIDTH
#  define W_WIDTH 800
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 600
# endif

# define EFILEISDIR	500
# define EFAILOPENFILE 501
# define EBADFILEEXT 502
# define EINVALARGCOUNT 502

# define EINVMAPHEIGHT 530
# define EMAPHBORDERERR 531
# define EMAPVBORDERERR 532
# define EMAPEMPTY 533
# define EMAPINVCHAR 533
# define EMAPTOOMANYPLAYERS 534
# define EMAPNOPLAYERS 535
# define EMAPPLAYEROUTOFBOUNDS 536
# define EMAPWALLMISSING 537

# define EMLXINIT 600
# define EMLXWINCREATE 601


# define KEY_COUNT 7
# define KEY_UP 0
# define KEY_DOWN 1
# define KEY_LEFT 2
# define KEY_RIGHT 3
# define KEY_A 4
# define KEY_D 5
# define KEY_ESC 6

# define M_BUTT_COUNT 5
# define M_LEFTBUTT 1
# define M_MIDDLEBUTT 2
# define M_RIGHTBUTT 3
# define M_SCROLLUP 4
# define M_SCRODOWN 5

# define RAY_HIT_N_OR_S 0
# define RAY_HIT_E_OR_W 1

# define MAP_ALLOWED_CHARS "01NSEW \n"
# define MAP_EMPTY_SPACE '0'
# define MAP_WALL '1'

typedef enum e_cardinal
{
	NORTH = 0,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
}	t_cardinal;

typedef enum e_direction_elements
{
	DIRX,
	DIRY,
	PLANEX,
	PLANEY
}	t_direction_elements;

/*
 *	bpp - bit per pixel
 *	ll	- line length
 */
typedef struct s_canvas
{
	void	*img;
	int		*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}	t_canvas;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct s_ipos
{
	int	x;
	int	y;
}	t_ipos;

/*
 *	(x, y)	position of the player on the map and in the "game"
 */
typedef struct s_player
{
	t_pos	pos;
}	t_player;

typedef struct s_ray
{
	int		side_hit;
	int		line_height;
	double	perp_dist;
	t_pos	dir;
	t_pos	delta_dist;
	t_pos	side_dist;
	t_pos	step;
}	t_ray;

/*
 *	gdata - Game data
 *
 *	player_direction: used to set starting direction of player, and to verify
 *	that only one player exists in a map
 */
typedef struct s_gdata
{
	void		*mlx;
	void		*win;
	t_canvas	canvas;
	int			file_fd;
	char		**map;
	int			map_height;
	int			map_width;
	int			tex_size;
	int			**textures;
	int			*tex_rgb;
	t_player	player;
	int			player_direction;
	int			keys[KEY_COUNT];
	t_ipos		win_center;
	t_pos		dir;
	t_pos		plane;
	double		time;
	double		old_time;
	double		frame_time;
	int			exit_status;
}	t_gdata;

// libft funcs
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *s, int n);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);

// parsing/check_arg.c
int		check_arg(t_gdata *gd, char *file_name);

// parsing/parse_file.c
int		parse_file_has_error(t_gdata *gdata, char *file_name);

// parsing/check_map.c
int		check_map_error(t_gdata *data);

// parsing/check_map_bounds_missing.c
int		check_map_bounds_missing(t_gdata *gd, char **map, int map_height);

// parsing/parse_textures.c
int		parse_texture_data(t_gdata *data, char *buffer);

// parsing/set_textures.c
int		set_textures(t_gdata *data, char *buffer, t_cardinal wall_dir);

int		check_error_in_args_map_or_init(t_gdata *gd, int argc, char **argv);

// error.c
void	ft_error(char *msg);

// utils.c
int		is_blank(char c);
void	close_fd(int *fd);
int		is_num(char c);

// init.c
int		init_gdata_has_error(t_gdata *gdata);

// cleanup.c
void    cleanup(t_gdata *gdata);
void	free_array(char **array);

// put_pixel.c
void	put_pixel(t_canvas *canvas, int x, int y, int color);

void	put_ver_line(t_canvas *canvas, int x, int y1, int y2, int color);

void	fill_all(t_canvas *canvas, int color);

// player_get_pos.c
int		player_outside_map(t_gdata *data, t_pos pos);
t_pos	player_get_pos_from_map(t_gdata *gdata);
double	pos_nsew_to_angle(char c);
t_pos	pos_init_to_invalid_pos(void);
t_pos	pos_set_to(double x, double y);

// key_events.c
int		key_press(int key, t_gdata *gdata);
int		key_release(int key, t_gdata *gdata);
void	handle_key_presses(t_gdata *data);

// render/texture.c
void	load_textures(t_gdata *data); //TO-DO: check for this, as there is no such file?

// debug.c
void	print_map_info(t_gdata *data);
void	test_textures(t_gdata *data, int *texture, int offset);
void	debug_print(t_gdata *data);

// render/rendering_function.c
int		rendering_function(void *param);
void	player_set_direction(t_gdata *gd);

// render/tex_colour.c
void	texture_func(t_gdata *data, t_ray ray, int x, int draw_start, int draw_end);

bool	mouse_moving_left(t_gdata *gd);
bool	mouse_moving_right(t_gdata *gd);
int		mouse_click_handler(int mbutt, int x, int y, void *gdata_ptr);

int		get_time_stamp();

// map_functions.c
char	map_get(t_gdata *gd, int x, int y);
void	map_set(t_gdata *gd, int x, int y, char c);

#endif
