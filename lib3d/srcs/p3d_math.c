/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p3d_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 15:44:47 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 13:59:57 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_p3d		p3d_add(t_p3d a, t_p3d b)
{
	return (t_p3d){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_p3d		p3d_sub(t_p3d a, t_p3d b)
{
	return (t_p3d){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_p3d		p3d_norm(t_p3d a)
{
	const float mag = sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);

	if (!mag)
		return (t_p3d){0, 0, 0};
	return (t_p3d){a.x / mag, a.y / mag, a.z / mag};
}

t_p3d		p3d_cross(t_p3d a, t_p3d b)
{
	t_p3d cross;

	cross.x = a.z * b.y - a.y * b.z;
	cross.y = a.x * b.z - a.z * b.x;
	cross.z = a.y * b.x - a.x * b.y;
	return (cross);
}

float		p3d_dot(t_p3d a, t_p3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
