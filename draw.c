/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:14:07 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 23:48:36 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	wrap_deg(float *f)
{
	*f = fmodf(360.0f + *f, 360.0f);
}

int	draw(void *param)
{
	t_data *data = (t_data *)param;
	size_t	i;
	t_p3d	*verts;
	t_p2d	*points;
	int		*visible_points;
	t_ipair	*lines;
	t_mat	mat_cam;
	const t_p2d raster_size = {(float)data->cfg.w, (float)data->cfg.h};
	const t_p2d canvas_size = {1.0f, 1.0f};

	img_clear(&data->img);

	if (data->input.k['w'])
		data->draw.cam.pos.z += 0.1f;
	if (data->input.k['s'])
		data->draw.cam.pos.z -= 0.1f;
	if (data->input.k['a'])
		data->draw.cam.pos.x -= 0.1f;
	if (data->input.k['d'])
		data->draw.cam.pos.x += 0.1f;
	if (data->input.k['q'])
		data->draw.cam.pos.y -= 0.1f;
	if (data->input.k['e'])
		data->draw.cam.pos.y += 0.1f;

	if (data->input.k['i'])
		data->draw.cam.rot.x += 1.0f;
	if (data->input.k['k'])
		data->draw.cam.rot.x -= 1.0f;
	if (data->input.k['j'])
		data->draw.cam.rot.y -= 1.0f;
	if (data->input.k['l'])
		data->draw.cam.rot.y += 1.0f;

	wrap_deg(&data->draw.cam.rot.x);
	wrap_deg(&data->draw.cam.rot.y);
	wrap_deg(&data->draw.cam.rot.z);

	printf("cam: %.2f %.2f %.2f, %.2f %.2f %.2f\n",
		data->draw.cam.pos.x, data->draw.cam.pos.y, data->draw.cam.pos.z,
		data->draw.cam.rot.x, data->draw.cam.rot.y, data->draw.cam.rot.z
	);

	i = 0;
	verts = (t_p3d *)data->draw.verts.data;
	points = (t_p2d *)data->draw.pts.data;
	visible_points = (int *)data->draw.visible_pts.data;
	mat_from_v3d(mat_cam, data->draw.cam);
	while (i < data->draw.verts.length)
	{
		visible_points[i] = p3d_project(&points[i], raster_size, canvas_size, verts[i], mat_cam);
		printf("%.2f, %.2f, %.2f -> %.2f, %.2f (%d)\n", verts[i].x, verts[i].y, verts[i].z, points[i].x, points[i].y, visible_points[i]);
		i++;
	}

	i = 0;
	lines = (t_ipair *)data->draw.lines.data;
	while (i < data->draw.lines.length)
	{
		if (visible_points[lines[i].a] && visible_points[lines[i].b])
			img_put_line(&data->img, points[lines[i].a], points[lines[i].b], data->draw.red);
		i++;
	}

	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	return 0;
}
