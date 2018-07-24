/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:24:30 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/24 15:30:27 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int mouse_hook(int btn, int x, int y, void *param)
{
	(void)param;
	printf("mouse_hook: %d (%d, %d)\n", btn, x, y);
	return 1;
}
