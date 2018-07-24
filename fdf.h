/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/24 15:40:46 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // aaa
# include "libft.h"
# include "get_next_line.h"
# include "vec.h"

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
** Wraps all the data structures so they can be passed to subfunctions
*/
typedef struct	s_data
{
	t_mlx		mlx;
}				t_data;

/*
** Events
*/
int key_hook(int key, void *param);
int mouse_hook(int btn, int x, int y, void *param);
int expose_hook(void *param);
int loop_hook(void *param);

/*
** Utilities
*/
void			die(t_data data, char *msg);

#endif
