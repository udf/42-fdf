/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 18:52:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/31 20:46:01 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	process_btn_changes(t_data *data)
{
	size_t i;
	t_input *input;

	i = 0;
	input = &data->input;
	while (i < MOUSE_MAX)
	{
		input->m.btn[i].changed = input->m.btn[i].down ^ input->m.btn[i].last;
		input->m.btn[i].last = input->m.btn[i].down;
		i++;
	}
}

int	loop(void *param)
{
	process_btn_changes((t_data *)param);
	draw((t_data *)param);
	return (0);
}
