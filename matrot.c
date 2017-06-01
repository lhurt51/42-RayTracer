/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 17:27:59 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 17:28:02 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/rtv1.h"
#include "includes/mat.h"

void	rot_xaxis(float tmp1[4][4], float tmp2[4][4], float ax)
{
	float	xmat[4][4];

	mat_identity(xmat);
	xmat[1][1] = cos(ax);
	xmat[1][2] = sin(ax);
	xmat[2][1] = -sin(ax);
	xmat[2][2] = cos(ax);
	mat_mult(tmp1, xmat, tmp2);
}

void	rot_yaxis(float tmp1[4][4], float tmp2[4][4], float ay)
{
	float	ymat[4][4];

	mat_identity(ymat);
	ymat[0][0] = cos(ay);
	ymat[0][2] = -sin(ay);
	ymat[2][0] = sin(ay);
	ymat[2][2] = cos(ay);
	mat_mult(tmp1, ymat, tmp2);
}

void	rot_zaxis(float tmp1[4][4], float tmp2[4][4], float az)
{
	float	zmat[4][4];

	mat_identity(zmat);
	zmat[0][0] = cos(az);
	zmat[0][1] = sin(az);
	zmat[1][0] = -sin(az);
	zmat[1][1] = cos(az);
	mat_mult(tmp1, zmat, tmp2);
}

void	mat_rotate(float matrix[4][4], float ax, float ay, float az)
{
	float	mat1[4][4];
	float	mat2[4][4];

	rot_yaxis(matrix, mat1, ay);
	rot_xaxis(mat1, mat2, ax);
	rot_zaxis(mat2, matrix, az);
}
