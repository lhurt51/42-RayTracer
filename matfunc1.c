/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicmatfunc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:02:57 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 18:03:00 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"

void	mat_copy(float source[4][4], float dest[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = source[i][j];
			j++;
		}
		i++;
	}
}

void	mat_mult(float mata[4][4], float matb[4][4], float dest[4][4])
{
	int i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			dest[i][j] = mata[i][0] * matb[0][j] + mata[i][1] * matb[1][j] +
			mata[i][2] * matb[2][j] + mata[i][3] * matb[3][j];
			j++;
		}
		i++;
	}
}

void	vec_mult_mat(t_vector *source, float mat[4][4], t_vector *dest)
{
	dest->x = source->x * mat[0][0] + source->y * mat[1][0]
		+ source->z * mat[2][0] + mat[3][0];
	dest->y = source->x * mat[0][1] + source->y * mat[1][1]
		+ source->z * mat[2][1] + mat[3][1];
	dest->z = source->x * mat[0][2] + source->y * mat[1][2]
		+ source->z * mat[2][2] + mat[3][2];
}
