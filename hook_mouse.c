/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:24:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 18:30:15 by mhoosen          ###   ########.fr       */
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
	data->input.m.btn[btn] = 1;
	printf("mouse_down: %d (%d, %d)\n", btn, x, y);
	return 0;
}

int on_mouseup(int btn, int x, int y, void *param)
{
	t_data *data = (t_data *)param;

	if (btn < 0 || btn > MOUSE_MAX)
		return 0;
	data->input.m.x = x;
	data->input.m.y = y;
	data->input.m.btn[btn] = 0;
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
