/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:14:07 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/29 05:26:32 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mat_set_modelview(t_mat ret, float distance, t_p3d pivot, t_p3d rot)
{
	(void)rot;
	mat_set_identity(ret);
	mat_translate(ret, -pivot.x, -pivot.y, -pivot.z);
	mat_rotate_z(ret, -rot.z);
	mat_rotate_y(ret, -rot.y);
	mat_rotate_x(ret, -rot.x);
	mat_translate(ret, 0.0f, 0.0f, -distance);
}

void	process_k_input(t_data *data)
{
	data->draw.rot.z += data->input.k[KEY_Left] ? 1.0f : 0.0f;
	data->draw.rot.z -= data->input.k[KEY_Right] ? 1.0f : 0.0f;
	data->draw.rot.x += data->input.k[KEY_Up] ? 1.0f : 0.0f;
	data->draw.rot.x -= data->input.k[KEY_Down] ? 1.0f : 0.0f;
}

void	process_m_input(t_mat world_to_cam, t_data *data)
{
	static char		m_scroll_last = 0;
	static t_p2d	m_old = {0.0f, 0.0f};
	t_p3d			m_rot;

	m_rot = (t_p3d){0, 0, 0};
	if (data->input.m.btn[2] && m_scroll_last != data->input.m.btn[2])
		m_old = (t_p2d){(float)data->input.m.x, (float)data->input.m.y};
	if (data->input.m.btn[2] || m_scroll_last != data->input.m.btn[2])
	{
		m_rot.x = ((float)data->input.m.y - m_old.y) / (float)data->cfg.w * 360.0f;
		m_rot.z = ((float)data->input.m.x - m_old.x) / (float)data->cfg.h * 360.0f;
	}
	mat_set_modelview(world_to_cam, data->draw.dist, data->draw.pivot,
		p3d_add(data->draw.rot, m_rot));
	if (!data->input.m.btn[2] && m_scroll_last != data->input.m.btn[2])
		data->draw.rot = p3d_add(data->draw.rot, m_rot);
	m_scroll_last = data->input.m.btn[2];
}

int	draw(void *param)
{
	t_data *data = (t_data *)param;
	size_t	i;
	t_p3d	*verts;
	t_p2d	*points;
	int		*visible_points;
	t_ipair	*lines;
	t_mat	world_to_cam;
	const t_p2d raster_size = {(float)data->cfg.w, (float)data->cfg.h};
	const t_p2d canvas_size = {1.0f, 1.0f};

	process_k_input(data);
	process_m_input(world_to_cam, data);

	i = 0;
	verts = (t_p3d *)data->draw.verts.data;
	points = (t_p2d *)data->draw.pts.data;
	visible_points = (int *)data->draw.visible_pts.data;
	while (i < data->draw.verts.length)
	{
		visible_points[i] = p3d_project(&points[i], raster_size, canvas_size, verts[i], world_to_cam);
		i++;
	}

	i = 0;
	lines = (t_ipair *)data->draw.lines.data;
	img_clear(&data->img);
	while (i < data->draw.lines.length)
	{
		if (visible_points[lines[i].a] && visible_points[lines[i].b])
			img_put_line(&data->img, points[lines[i].a], points[lines[i].b], data->draw.red);
		i++;
	}

	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	return 0;
}
