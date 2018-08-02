/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_mult.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:57:56 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 14:00:22 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void	mat_mult(const t_mat m1, const t_mat m2, t_mat dest)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = 0;
			dest[i][j] += m1[i][0] * m2[0][j];
			dest[i][j] += m1[i][1] * m2[1][j];
			dest[i][j] += m1[i][2] * m2[2][j];
			dest[i][j] += m1[i][3] * m2[3][j];
			j++;
		}
		i++;
	}
}
