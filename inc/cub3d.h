/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:25 by avalsang          #+#    #+#             */
/*   Updated: 2025/08/09 15:30:15 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"

/* --------------------------------- macros --------------------------------- */

# ifndef W_WIDTH
#  define W_WIDTH 1024
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 768
# endif

# define WALL_MAX_CLOSENESS 0.05

# define EMLXINIT 5
# define EMLXWINCREATE 6
# define EMLXIMGCREATE 7

# define EFILEISDIR	10
# define EFAILOPENFILE 11
# define EBADFILEEXT 12
# define EINVARGS 13

# define EINVMAP 20
# define EMAPHBORDER 21
# define EMAPVBORDER 22
# define EMAPEMPTY 23
# define EMAPINVCHAR 24
# define ERR_MALLOC 25
# define E_INV_PLAYER 26
# define EMAPWALLMISSING 28
# define EMISSINGTEXTURE 29
# define EMAPTEXINVALIDFILENAME 30
# define EMAPTEXERROR 31
# define ESPRITEERROR 32

# define KEY_COUNT 9
# define KEY_UP 0
# define KEY_DOWN 1
# define KEY_LEFT 2
# define KEY_RIGHT 3
# define KEY_A 4
# define KEY_D 5
# define KEY_ESC 6
# define KEY_PITCH_UP 7
# define KEY_PITCH_DOWN 8

# define M_BUTT_COUNT 5
# define M_LEFTBUTT 1
# define M_MIDDLEBUTT 2
# define M_RIGHTBUTT 3
# define M_SCROLLUP 4
# define M_SCRODOWN 5

# define RAY_HIT_N_OR_S 0
# define RAY_HIT_E_OR_W 1

# define MAP_EMPTY_SPACE '0'
# define MAP_WALL '1'

/* --------------------------------- Structs -------------------------------- */

typedef enum e_action
{
	SET,
	GET
}	t_action;

typedef enum e_cardinal
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	FLOOR,
	CEILING,
	DOOR,
}	t_cardinal;

typedef enum e_direction_elements
{
	DIRX,
	DIRY,
	PLANEX,
	PLANEY
}	t_direction_elements;

typedef struct s_texinfo
{
	double	wall_x;
	double	tex_pos;
	double	step;
	int		dir;
}	t_texinfo;

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
	int		draw_start;
	int		draw_end;
	int		hit_door;
	int		door_side;
	double	perp_dist;
	t_pos	dir;
	t_pos	delta_dist;
	t_pos	side_dist;
	t_pos	step;
}	t_ray;

typedef struct s_minimap
{
	int		height;
	int		width;
	int		**colour_array;
}	t_minimap;

typedef struct s_sprite
{
	int		tex;
	double	x;
	double	y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_size;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
}	t_sprite;

typedef struct s_door
{
	int		x;
	int		y;
	int		status;
	int		old_time;
	float	offset;
}	t_door;

typedef struct s_floor
{
	float		step_x;
	float		step_y;
	float		floor_x;
	float		floor_y;
	float		row_dist;
	t_ray		ray;
	bool		is_floor;
}	t_floor;

typedef struct set_weapon
{
	int			**model;
	int			current;
	int			width;
	int			height;
	int			frame;
	int			state;
	int			auto_fire;
}	t_weapon;

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
	int			keys[KEY_COUNT];
	t_pos		dir;
	t_pos		plane;
	double		time;
	double		old_time;
	double		frame_time;
	int			exit_status;
	t_door		door[16];
	int			num_doors;
	t_minimap	minimap;
	double		z_buffer[W_WIDTH];
	t_weapon	weapon;
	double		pitch;
	int			num_sprite_tex;
	int			num_sprite_pos;
	int			**sprite_tex;
	t_sprite	sprite[4];
}	t_gdata;

/* ------------------------------- libft funcs ------------------------------ */

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
void	ft_putstr_fd(char *s, int fd);

/* --------------------------------- parsing -------------------------------- */

// parsing/check_arg.c
int		check_arg(t_gdata *gd, char *file_name);

// parsing/check_map.c
int		check_map(t_gdata *data);

// parsing/check_map_bounds.c
int		check_map_bounds(t_gdata *gd, char **map, int map_height);

// parsing/map_fill.c
int		map_fill(t_gdata *gd, char **map, int fd);

// parsing/parse_file.c
int		parse_file(t_gdata *gdata, char *file_name);
bool	buffer_has_map_data(char *buffer);

// parsing/parse_textures.c
int		parse_textures(t_gdata *data, char *buffer);

// parsing/set_textures.c
void	set_textures(t_gdata *data, char *buffer, t_cardinal wall_dir);
void	init_img(t_canvas *img);
int		*parse_xpm(t_gdata *data, char *path);
char	*get_texture_path(char *buffer);

// parsing/set_sprite.c
void	set_sprite(t_gdata *gd, char *path);
void	set_sprite_pos(t_gdata *gd, char *buffer);

/* --------------------------------- render --------------------------------- */

// render/door.c
void	find_doors(t_gdata *gd);
void	wall_anim(t_gdata *gd);
void	open_sesame(t_gdata *gd);
int		door_calc(t_gdata *gd, t_ray *ray, t_ipos *map_pos);

// render/draw_wall.c
void	draw_wall(t_gdata *data, t_ray ray, int x);

// render/floor_cast.c
void	floor_cast(t_gdata *gd);

// render/minimap.c
int		**minimap_colours(t_gdata *gd);
void	render_minimap(t_gdata *gd);

// render/put_pixel.c
void	put_pixel(t_canvas *canvas, int x, int y, int color);
int		blend(int fg, int bg, int alpha);
int		get_pixel(t_canvas *canvas, int x, int y);

// render/ray_create.c
t_ray	ray_create(t_gdata *gd, int x, t_ipos *map_pos);

// render/render_loop.c
int		render_loop(void *param);

// render/weapon_anim.c
void	weapon_shoot(t_gdata *gd);
void	weapon_holster(t_gdata *gd);
void	weapon_equip(t_gdata *gd);
void	weapon_animate(t_gdata *gd);

// render/weapon.c
int		set_weapon(t_gdata *gd);
void	draw_weapon(t_gdata *gd);

/* -------------------------------- the rest -------------------------------- */

// cleanup.c
void	cleanup(t_gdata *gdata);
void	free_array(void **array);
void	free_data(t_gdata *data);

// debug.c
void	debug_print(t_gdata *data);

// error.c
void	ft_error(char *msg);
void	ft_perror(void);
int		handle_error(int return_code, char **argv);

// fps.c
void	update_frame_time(t_gdata *gd);

// init.c
int		init_map_data(t_gdata *gd);
int		init_mlx(t_gdata *gd);

// key_events.c
int		key_press(int key, t_gdata *gdata);
int		key_release(int key, t_gdata *gdata);
void	handle_key_presses(t_gdata *data);
void	rotate_player(t_gdata *gd, double rot_speed);

// key_helpers.c
void	weapon_switch(t_gdata *gd, int key);
void	modify_pitch(t_gdata *gd, double move_speed);
int		wall_status(t_gdata *gd, int x, int y);

// map_functions.c
char	map_get(t_gdata *gd, int x, int y);
void	map_set(t_gdata *gd, int x, int y, char c);
t_ipos	pos_dtoi(t_pos dpos);

// mouse_events.c
int		mouse_click(int button, int x, int y, t_gdata *gd);
int		mouse_release(int button, int x, int y, t_gdata *gd);

// program_name.c
char	*get_program_name(void);
void	set_program_name(char *program_name);

// sprite.c
void	draw_sprite(t_gdata *gd);

// utils.c
int		is_blank(char c);
void	close_fd(int *fd);
int		is_num(char c);
int		exit_status(t_gdata *data, int exit_code);
int		failed(int return_value);

#endif
