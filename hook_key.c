/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:24:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/29 00:35:30 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int on_keydown(int key, void *param)
{
	t_data *data = (t_data *)param;

	if (key < 0 || key > KEY_MAX)
		return 0;
	data->input.k[key] = 1;
	printf("keydown_hook: %d\n", key);
	return 0;
}

int on_keyup(int key, void *param)
{
	t_data *data = (t_data *)param;

	if (key < 0 || key > KEY_MAX)
		return 0;

	if (data->input.k['i'])
		data->draw.up_pos.y += 0.1f;
	if (data->input.k['k'])
		data->draw.up_pos.y -= 0.1f;
	if (data->input.k['j'])
		data->draw.up_pos.x -= 0.1f;
	if (data->input.k['l'])
		data->draw.up_pos.x += 0.1f;
	if (data->input.k['u'])
		data->draw.up_pos.z -= 0.1f;
	if (data->input.k['o'])
		data->draw.up_pos.z += 0.1f;

	data->input.k[key] = 0;
	printf("keyup_hook: %d\n", key);
	if (key == KEY_Escape)
		die(*data, "Quit pressed!");

	return 0;
}
