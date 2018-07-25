/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/25 23:56:03 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // aaa
# include "libft.h"
# include "lib3d.h"
# include "get_next_line.h"
# include "vec.h"

typedef unsigned int t_uint;

/*
** Keycodes (because X11 keycodes don't work on OSX)
** mlx uses the codes found in /usr/include/keysymdef.h
*/
# define KEY_Escape      0xff1b
# define KEY_q           0x0071
# define KEY_Left        0xff51
# define KEY_Up          0xff52
# define KEY_Right       0xff53
# define KEY_Down        0xff54

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
}				t_cfg;

/*
** Stores an mlx image with the information from mlx_get_data_addr
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
}				t_img;

/*
** Stores state variables used for drawing
*/
typedef struct	s_draw
{
	t_uint		red;
	t_p2d		q;
	t_p2d		d;
}				t_draw;

/*
** Wraps all the data structures so they can be passed to subfunctions
*/
typedef struct	s_data
{
	const t_cfg	cfg;
	t_mlx		mlx;
	t_img		img;
	t_draw		draw;
}				t_data;

/*
** Events
*/
int key_hook(int key, void *param);
int mouse_hook(int btn, int x, int y, void *param);
int draw(void *param);

/*
** Utilities
*/
int				get_endian(void);
unsigned int	swap_endian(unsigned int n);
t_img			make_img(void *mlx_ptr, int w, int h);
unsigned int	make_colour(void *mlx_ptr, t_img *img, int colour);
void			die(t_data data, char *msg);

#endif
