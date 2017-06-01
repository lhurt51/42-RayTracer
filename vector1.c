/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vector.h"

t_vector	vect_cross(t_vector *v1, t_vector *v2)
{
	t_vector	res;

	res.x = (v1->y * v2->z) - (v1->z * v2->y);
	res.y = (v1->z * v2->x) - (v1->x * v2->z);
	res.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (res);
}

float		vect_dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	vect_diff(t_vector *v1, t_vector *v2)
{
	t_vector	rtn;

	rtn = vect_scale(vect_dot(v1, v2), v2);
	rtn = vect_sub(v1, &rtn);
	return (rtn);
}

double		vect_norm(t_vector *v)
{
	double		dist;
	double		tmp;

	if ((dist = vect_dot(v, v)) == 0.0f)
		return (dist);
	tmp = INVSQRTF(dist);
	*v = vect_scale(tmp, v);
	return (dist);
}
