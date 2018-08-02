/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 21:12:22 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 15:09:49 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_mousedown(int btn, int x, int y, t_data *data)
{
	const char	*keys = data->input.k;
	float		scroll_tick;
	float		*scroll_v;

	if (btn < 0 || btn > MOUSE_MAX)
		return (0);
	data->input.m.x = x;
	data->input.m.y = y;
	data->input.m.btn[btn].down = 1;
	scroll_v = keys[KEY_CTRL] ? &data->draw.z_scale : &data->draw.dist;
	scroll_tick = keys[KEY_CTRL] ? data->cfg.z_scale_tick : data->cfg.zoom_tick;
	scroll_tick *= keys[KEY_ALT] ? data->cfg.zoom_mult : 1.0f;
	if (btn == MOUSE_UP)
		*scroll_v -= scroll_tick;
	if (btn == MOUSE_DOWN)
		*scroll_v += scroll_tick;
	*scroll_v = MAX(*scroll_v, 1.0f);
	return (0);
}

int	on_mouseup(int btn, int x, int y, t_data *data)
{

	if (btn < 0 || btn > MOUSE_MAX)
		return (0);
	data->input.m.x = x;
	data->input.m.y = y;
	data->input.m.btn[btn].down = 0;
	return (0);
}

int	on_mousemove(int x, int y, t_data *data)
{
	data->input.m.x = x;
	data->input.m.y = y;
	return (0);
}
