/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:14:07 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 13:53:05 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mat_set_modelview(t_mat ret, float distance, t_p3d pivot, t_p3d rot)
{
	mat_set_identity(ret);
	mat_translate(ret, -pivot.x, -pivot.y, -pivot.z);
	mat_rotate_z(ret, -rot.z);
	mat_rotate_y(ret, -rot.y);
	mat_rotate_x(ret, -rot.x);
	mat_translate(ret, 0.0f, 0.0f, -distance);
}

void	img_put_line3(t_img *img, t_p3d a, t_p3d b, t_uint col)
{
	//printf("%f %f\n", a.z, b.z);
	img_put_line(img, (t_p2d){a.x, a.y}, (t_p2d){b.x, b.y}, col);
}

t_p3d	z_scale(t_p3d p, float scale)
{
	return ((t_p3d){p.x, p.y, p.z / scale});
}

void	draw_pivot(t_data *data)
{
	const char	pixmap[5][5] = {
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0}
	};
	int			x;
	int			y;

	x = 0;
	while (x < 5)
	{
		y = 0;
		while (y < 5)
		{
			if (pixmap[x][y])
				img_put_pixel(&data->img,
					data->cfg.w / 2 + x - 2, data->cfg.h / 2 + y - 2,
					data->draw.col_pivot);
			y++;
		}
		x++;
	}
}

int		draw(t_data *data)
{
	size_t		i;
	t_p3d		*verts;
	t_p3d		*points;
	t_ipair		*lines;
	t_mat		world_to_cam;
	const t_p2d	raster_size = {(float)data->cfg.w, (float)data->cfg.h};
	const float	dist = data->draw.ortho ? data->draw.dist : 0;

	mat_set_modelview(world_to_cam, data->draw.dist, data->draw.pivot,
		p3d_add(data->draw.rot, data->draw.m_rot));
	i = 0;
	verts = (t_p3d *)data->draw.verts.data;
	points = (t_p3d *)data->draw.pts.data;
	while (i < data->draw.verts.length)
	{
		points[i] = p3d_project(dist, raster_size, z_scale(verts[i], data->draw.z_scale), world_to_cam);
		i++;
	}
	i = 0;
	lines = (t_ipair *)data->draw.lines.data;
	img_clear(&data->img);
	while (i < data->draw.lines.length)
	{
		if (points[lines[i].a].z > 0 && points[lines[i].b].z > 0)
			img_put_line3(&data->img, points[lines[i].a], points[lines[i].b], data->draw.red);
		i++;
	}
	draw_pivot(data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	return (0);
}
