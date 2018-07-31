/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 21:12:22 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/31 09:11:03 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int on_mousedown(int btn, int x, int y, void *param)
{
	t_data *data = (t_data *)param;

	if (btn < 0 || btn > MOUSE_MAX)
		return 0;
	data->input.m.x = x;
	data->input.m.y = y;
	data->input.m.btn[btn].down = 1;
	printf("mouse_down: %d (%d, %d)\n", btn, x, y);
	return 0;
}

int on_mouseup(int btn, int x, int y, void *param)
{
	t_data *data = (t_data *)param;
	float scroll_tick;
	float *scroll_v;

	if (btn < 0 || btn > MOUSE_MAX)
		return 0;
	data->input.m.x = x;
	data->input.m.y = y;
	data->input.m.btn[btn].down = 0;
	scroll_v = data->input.k[KEY_Ctrl] ? &data->draw.z_scale : &data->draw.dist;
	scroll_tick = data->input.k[KEY_Ctrl] ? data->cfg.z_scale_tick : data->cfg.zoom_tick;
	scroll_tick *= data->input.k[KEY_Shift] ? data->cfg.zoom_mult : 1.0f;
	if (btn == MOUSE_Up)
		*scroll_v -= scroll_tick;
	if (btn == MOUSE_Down)
		*scroll_v += scroll_tick;
	*scroll_v = MAX(*scroll_v, 1.0f);
	printf("mouse_up: %d (%d, %d)\n", btn, x, y);
	return 0;
}

int on_mousemove(int x, int y, void *param)
{
	t_data *data = (t_data *)param;

	data->input.m.x = x;
	data->input.m.y = y;
	return 0;
}
