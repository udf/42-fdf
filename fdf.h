/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/06 12:50:03 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"
# include "lib3d.h"
# include "get_next_line.h"
# include "vec.h"

typedef unsigned int	t_uint;

/*
** Keycodes
*/
# define KEY_ESC		53
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_DOWN		125
# define KEY_UP			126
# define KEY_ALT		261
# define KEY_CTRL		256
# define KEY_SHIFT		257
# define KEY_M			46
# define KEY_W			13
# define KEY_S			1
# define KEY_A			0
# define KEY_D			2
# define KEY_Q			12
# define KEY_E			14
# define KEY_R			15

# define MOUSE_LEFT		1
# define MOUSE_UP		4
# define MOUSE_DOWN		5

# define KEY_MAX 0xffff
# define MOUSE_MAX 10

/*
** Event codes
*/
# define KEY_PRESS		2
# define KEY_RELEASE	3
# define BUTTON_PRESS	4
# define BUTTON_RELEASE	5
# define MOTION_NOTIFY	6

/*
** A 2D point but with integers
*/
typedef struct	s_ip2d
{
	ssize_t		x;
	ssize_t		y;
}				t_ip2d;

/*
** A pair of unsigned ints (colours)
*/
typedef struct	s_colpair
{
	t_uint		a;
	t_uint		b;
}				t_colpair;

/*
** A pair of indicies, used to define which points connect to form a line
*/
typedef struct	s_ipair
{
	size_t		a;
	size_t		b;
}				t_ipair;

/*
** Stores various mlx handles
*/
typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

/*
** Stores configurable variables (runtime constants)
*/
typedef struct	s_cfg
{
	int			w;
	int			h;
	float		zoom_tick;
	float		z_scale_tick;
	float		zoom_mult;
}				t_cfg;

/*
** Stores an mlx image with the information from mlx_get_data_addr
** as well as a z-buffer
*/
typedef struct	s_img
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			stride;
	int			endian;
	int			w;
	int			h;
	float		*z_buf;
}				t_img;

/*
** Stored variables related to drawing
*/
typedef struct	s_draw
{
	t_p3d		pivot;
	t_p3d		rot;
	t_p3d		m_rot;
	float		dist;
	float		z_scale;
	char		ortho;
	size_t		map_w;
	size_t		map_h;
	t_vec		verts;
	t_vec		lines;
	t_vec		pts;
	t_uint		col_pivot;
	t_vec		colmap;
	int			colmap_offset;
}				t_draw;

typedef struct	s_btn
{
	char		down;
	char		changed;
	char		last;
}				t_btn;

typedef struct	s_mouse
{
	int			x;
	int			y;
	t_btn		btn[MOUSE_MAX];
}				t_mouse;

typedef struct	s_input
{
	t_mouse		m;
	char		k[KEY_MAX];
}				t_input;

/*
** Wraps all the data structures so they can be passed to subfunctions
*/
typedef struct	s_data
{
	const t_cfg	cfg;
	t_mlx		mlx;
	t_input		input;
	t_img		img;
	t_draw		draw;
}				t_data;

/*
** Input processing and events
*/
int				on_keyup(int key, t_data *data);
int				on_keydown(int key, t_data *data);
int				on_mouseup(int btn, int x, int y, t_data *data);
int				on_mousedown(int btn, int x, int y, t_data *data);
int				on_mousemove(int x, int y, t_data *data);

int				loop(t_data *data);
int				draw(t_data *data);

/*
** Utilities
*/
float			flerpf(float frac, float start, float end);
t_p2d			t_p2d_lerp(float frac, t_p2d start, t_p2d end);
t_p2d			p2d_roundf(t_p2d p);

t_img			make_img(void *mlx_ptr, int w, int h);
void			die(t_data data, char *msg);

t_ip2d			ip2d_add(t_ip2d a, t_ip2d b);
int				ip2d_in_rect(t_ip2d p, size_t w, size_t h);
size_t			ip2d_to_i(t_ip2d p, size_t w);

t_uint			cmap_get(t_draw *draw, int height);
t_uint			colour_lerp(float n, t_uint a, t_uint b);

/*
** Image drawing
*/
void			img_put_pixel(t_img *img, int x, int y, t_uint col);
int				line_clip(t_p2d *a, t_p2d *b, float w, float h);
void			img_put_line(t_img *img, t_p2d a, t_p2d b, t_uint col);
void			img_clear(t_img *img);

/*
** Map reading
*/
char			*load_map(t_draw *draw, char *path);
char			*load_colour_map(t_data *data, int ac, char **av);

#endif
