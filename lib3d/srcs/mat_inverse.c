/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_inverse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 21:56:27 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 14:14:29 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void	mat_inverse(t_mat inv, const t_mat src)
{
	const t_p3d u = {src[0][0], src[0][1], src[0][2]};
	const t_p3d v = {src[1][0], src[1][1], src[1][2]};
	const t_p3d w = {src[2][0], src[2][1], src[2][2]};
	const t_p3d t = {-src[3][0], -src[3][1], -src[3][2]};

	mat_set_row(inv[0], (float[4]){u.x, v.x, w.x, 0});
	mat_set_row(inv[1], (float[4]){u.y, v.y, w.y, 0});
	mat_set_row(inv[2], (float[4]){u.z, v.z, w.z, 0});
	mat_set_row(inv[3],
		(float[4]){p3d_dot(u, t), p3d_dot(v, t), p3d_dot(w, t), 1});
}
