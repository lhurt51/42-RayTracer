/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matfunc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 18:06:27 by lhurt             #+#    #+#             */
/*   Updated: 2016/12/06 18:06:30 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mat_identity(float mat[4][4])
{
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;
	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;
	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;
	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
}

void	mat_translate(float matrix[4][4], float tx, float ty, float tz)
{
	float	tmat[4][4];
	float	tmp[4][4];

	mat_identity(tmat);
	tmat[3][0] = tx;
	tmat[3][1] = ty;
	tmat[3][2] = tz;
	mat_mult(matrix, tmat, tmp);
	mat_copy(tmp, matrix);
}

void	mat_scale(float matrix[4][4], float sx, float sy, float sz)
{
	float	smat[4][4];
	float	tmp[4][4];

	mat_identity(smat);
	smat[0][0] = sx;
	smat[1][1] = sy;
	smat[2][2] = sz;
	mat_mult(matrix, smat, tmp);
	mat_copy(tmp, matrix);
}

// void	project(t_vertex *vertex)
// {
// 	if (!vertex->aligned.z)
// 		vertex->aligned.z = 1;
// 	vertex->screen.x = FOCAL_DISTANCE * vertex->aligned.x / vertex->aligned.z +
// 	W_XORIGIN;
// 	vertex->screen.y = FOCAL_DISTANCE * vertex->aligned.y / vertex->aligned.z +
// 	W_YORIGIN;
// }
