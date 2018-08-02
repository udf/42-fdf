/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 18:52:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 21:36:33 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_btn_changes(t_data *data)
{
	size_t	i;
	t_input	*input;

	i = 0;
	input = &data->input;
	while (i < MOUSE_MAX)
	{
		input->m.btn[i].changed = input->m.btn[i].down ^ input->m.btn[i].last;
		input->m.btn[i].last = input->m.btn[i].down;
		i++;
	}
}

static void	process_k_input(t_data *data)
{
	const float	move_mult = data->input.k[KEY_ALT] ? 1.0f : 0.1f;
	t_p2d		diff;

	data->draw.rot.z += data->input.k[KEY_LEFT] ? 1.0f : 0.0f;
	data->draw.rot.z -= data->input.k[KEY_RIGHT] ? 1.0f : 0.0f;
	data->draw.rot.x += data->input.k[KEY_UP] ? 1.0f : 0.0f;
	data->draw.rot.x -= data->input.k[KEY_DOWN] ? 1.0f : 0.0f;
	data->draw.pivot.z += data->input.k[KEY_E] ? move_mult : 0.0f;
	data->draw.pivot.z -= data->input.k[KEY_Q] ? move_mult : 0.0f;
	if (data->input.k[KEY_D] || data->input.k[KEY_A])
	{
		diff.x = cos_deg(data->draw.rot.z) * (data->input.k[KEY_A] ? -1 : 1);
		diff.y = sin_deg(data->draw.rot.z) * (data->input.k[KEY_A] ? -1 : 1);
		data->draw.pivot.x += diff.x * move_mult;
		data->draw.pivot.y += diff.y * move_mult;
	}
	if (data->input.k[KEY_W] || data->input.k[KEY_S])
	{
		diff.x = sin_deg(data->draw.rot.z) * (data->input.k[KEY_W] ? 1 : -1);
		diff.y = cos_deg(data->draw.rot.z) * (data->input.k[KEY_W] ? -1 : 1);
		data->draw.pivot.x += diff.x * move_mult;
		data->draw.pivot.y += diff.y * move_mult;
	}
}

static void	process_m_input(t_data *data)
{
	static t_p2d	m_old = {0.0f, 0.0f};
	const t_mouse	mouse = data->input.m;
	t_p3d			*m_rot;

	m_rot = &data->draw.m_rot;
	if (mouse.btn[1].down && mouse.btn[1].changed)
		m_old = (t_p2d){(float)mouse.x, (float)mouse.y};
	if (mouse.btn[1].down || mouse.btn[1].changed)
	{
		m_rot->x = ((float)mouse.y - m_old.y) / (float)data->cfg.w * 360.0f;
		m_rot->z = ((float)mouse.x - m_old.x) / (float)data->cfg.h * 360.0f;
	}
	if (!mouse.btn[1].down && mouse.btn[1].changed)
	{
		data->draw.rot = p3d_add(data->draw.rot, *m_rot);
		*m_rot = (t_p3d){0, 0, 0};
	}
}

void	project(t_data *data)
{
	size_t		i;
	t_p3d		*verts;
	t_p3d		*points;
	t_mat		world_to_cam;
	const t_p2d	raster_size = {(float)data->cfg.w, (float)data->cfg.h};

	mat_set_modelview(world_to_cam, data->draw.dist, data->draw.pivot,
		p3d_add(data->draw.rot, data->draw.m_rot));
	i = 0;
	verts = (t_p3d *)data->draw.verts.data;
	points = (t_p3d *)data->draw.pts.data;
	while (i < data->draw.verts.length)
	{
		points[i] = p3d_project(data->draw.ortho ? data->draw.dist : 0,
			raster_size, z_scale(verts[i], data->draw.z_scale), world_to_cam);
		i++;
	}
}

int			loop(t_data *data)
{
	process_btn_changes(data);
	process_k_input(data);
	process_m_input(data);
	project(data);
	draw(data);
	return (0);
}
