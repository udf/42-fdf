/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_set_identity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:57:56 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 14:11:00 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void	mat_set_identity(t_mat m)
{
	mat_set_row(m[0], (float[4]){1, 0, 0, 0});
	mat_set_row(m[1], (float[4]){0, 1, 0, 0});
	mat_set_row(m[2], (float[4]){0, 0, 1, 0});
	mat_set_row(m[3], (float[4]){0, 0, 0, 1});
}