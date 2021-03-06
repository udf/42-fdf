/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:24:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/06 12:43:52 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_keydown(int key, t_data *data)
{
	if (key < 0 || key > KEY_MAX)
		return (0);
	data->input.k[key] = 1;
	return (0);
}

int	on_keyup(int key, t_data *data)
{
	if (key < 0 || key > KEY_MAX)
		return (0);
	data->input.k[key] = 0;
	if (key == KEY_M)
		data->draw.ortho = !data->draw.ortho;
	if (key == KEY_R)
		data->draw.pivot = (t_p3d){(float)data->draw.map_w / 2,
									(float)data->draw.map_h / 2, 0};
	if (key == KEY_ESC)
		die(*data, "Quit pressed!");
	return (0);
}
