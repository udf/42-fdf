/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:14:07 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/28 19:25:48 by mhoosen          ###   ########.fr       */
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
	t_mat	cam_to_world;
	t_mat	world_to_cam;
	const t_p2d raster_size = {(float)data->cfg.w, (float)data->cfg.h};
	const t_p2d canvas_size = {1.0f, 1.0f};

	img_clear(&data->img);

	if (data->input.k['w'])
		data->draw.cam_pos.y += 0.1f;
	if (data->input.k['s'])
		data->draw.cam_pos.y -= 0.1f;
	if (data->input.k['a'])
		data->draw.cam_pos.x -= 0.1f;
	if (data->input.k['d'])
		data->draw.cam_pos.x += 0.1f;
	if (data->input.k['q'])
		data->draw.cam_pos.z -= 0.1f;
	if (data->input.k['e'])
		data->draw.cam_pos.z += 0.1f;

	printf("cam: %.2f %.2f %.2f\n",
		data->draw.cam_pos.x, data->draw.cam_pos.y, data->draw.cam_pos.z
	);

	i = 0;
	verts = (t_p3d *)data->draw.verts.data;
	points = (t_p2d *)data->draw.pts.data;
	visible_points = (int *)data->draw.visible_pts.data;
	mat_look_at(cam_to_world, data->draw.cam_pos, (t_p3d){0.0f, 0.0f, 0.0f});
	mat_inverse(world_to_cam, cam_to_world);
	while (i < data->draw.verts.length)
	{
		visible_points[i] = p3d_project(&points[i], raster_size, canvas_size, verts[i], world_to_cam);
		//printf("%.2f, %.2f, %.2f -> %.2f, %.2f (%d)\n", verts[i].x, verts[i].y, verts[i].z, points[i].x, points[i].y, visible_points[i]);
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
