/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 08:32:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/06 12:27:32 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB3D_H
# define LIB3D_H
# include <math.h>
# include <stddef.h>

# ifndef ABS
#  define ABS(x) ((x < 0) ? -(x) : (x))
# endif

/*
** Your standard 2D point
*/
typedef struct	s_p2d
{
	float		x;
	float		y;
}				t_p2d;

/*
** Your standard 3D point
*/
typedef struct	s_p3d
{
	float		x;
	float		y;
	float		z;
}				t_p3d;

/*
** A transformation matrix
** (it's actually just a float*)
*/
typedef float	t_mat[4][4];

float			sin_deg(float deg);
float			cos_deg(float deg);

/*
** Matrix stuff
*/
void			mat_copy(t_mat dest, const t_mat src);
void			mat_set_row(float dest[4], float data[4]);

/*
** Sets a matrix to an identity matrix (aka a "blank" matrix)
*/
void			mat_set_identity(t_mat m);

/*
** Multiplies (combines) two matricies and stores the result in dest
*/
void			mat_mult(const t_mat m1, const t_mat m2, t_mat dest);

/*
** Transforms a 3d point using a matrix
*/
t_p3d			p3d_transform(const t_p3d src, const t_mat m);

/*
** Projects a 3d point using a camera matrix (use mat_from_v3d to get one)
** The (x, y) of the returned point are screen coordinates while the z is the
** depth of the point (if depth <= 0, then the point is behind the camera)
** If distance is 0, then a perspective projection is used, else orthographic
*/
t_p3d			p3d_project(float distance, t_p2d r_size, t_p3d p_world,
						const t_mat mat_cam);

/*
** Applies a translation to a matrix
*/
void			mat_translate(t_mat dest, float x, float y, float z);

/*
** Applies a scale operation to a matrix
*/
void			mat_scale(t_mat dest, float x, float y, float z);

/*
** Constructs a camera matrix from a camera position and a point
*/
void			mat_look_at(t_mat dest, t_p3d eye, t_p3d center, t_p3d up);

/*
** Applies a (x, y, z) rotation to a matrix
*/
void			mat_rotate_x(t_mat dest, float x);
void			mat_rotate_y(t_mat dest, float y);
void			mat_rotate_z(t_mat dest, float z);

/*
** Inverts a matrix
** from
** [ux uy uz  0]
** [vx vy vz  0]
** [wx wy wz  0]
** [tx ty tz  1]
** to
** [  ux   vx   wx  0]
** [  uy   vy   wy  0]
** [  uz   vz   wz  0]
** [-u.t -v.t -w.t  1]
*/
void			mat_inverse(t_mat inv, const t_mat src);

/*
** Various math functions for 3d points
*/
t_p3d			p3d_add(t_p3d a, t_p3d b);
t_p3d			p3d_sub(t_p3d a, t_p3d b);
t_p3d			p3d_norm(t_p3d a);
t_p3d			p3d_cross(t_p3d a, t_p3d b);
float			p3d_dot(t_p3d a, t_p3d b);

#endif
