/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p3d_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 15:37:35 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 14:03:27 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"
#include <stdio.h>

t_p3d	p3d_project(float distance, t_p2d r_size, t_p3d p_world,
						const t_mat mat_cam)
{
	const float	min_dim = fminf(r_size.x, r_size.y);
	const t_p2d	c_size = {r_size.x / min_dim, r_size.y / min_dim};
	t_p3d		p_camera;
	t_p3d		p_raster;
	t_p2d		p_screen;

	p_camera = p3d_transform(p_world, mat_cam);
	distance = distance ? distance : -p_camera.z;
	p_screen.x = p_camera.x / distance;
	p_screen.y = p_camera.y / distance;
	if (ABS(p_screen.x) > c_size.x && ABS(p_screen.y) > c_size.y)
		return ((t_p3d){0, 0, 0});
	p_raster.x = (p_screen.x / c_size.x + 0.5f) * r_size.x;
	p_raster.y = (p_screen.y / c_size.y + 0.5f) * r_size.y;
	p_raster.z = -p_camera.z;
	return (p_raster);
}
