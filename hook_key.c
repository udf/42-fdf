/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:24:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 18:33:19 by mhoosen          ###   ########.fr       */
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
	data->input.k[key] = 0;
	printf("keyup_hook: %d\n", key);
	if (key == KEY_Escape)
		die(*data, "Quit pressed!");
	return 0;
}
