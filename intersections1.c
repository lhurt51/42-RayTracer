/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray_trace.h"

int			ray_intersect_cone(t_ray *ray, t_cone *cn, double *t, int flip)
{
	t_vector	dist;
	double		a;
	double		b;
	double		tmp[4];

	dist = vect_sub(&ray->start, &cn->pos);
	a = vect_dot(&ray->dir, &ray->dir) - ((1 + SQ(cn->radius)))
		* vect_dot(&ray->dir, &cn->rot) * vect_dot(&ray->dir, &cn->rot);
	b = 2 * (vect_dot(&ray->dir, &dist) - ((1 + SQ(cn->radius)))
		* vect_dot(&ray->dir, &cn->rot) * vect_dot(&dist, &cn->rot));
	tmp[3] = SQ(b) - 4 * a * (vect_dot(&dist, &dist) - ((1 + SQ(cn->radius)))
		* vect_dot(&dist, &cn->rot) * vect_dot(&dist, &cn->rot));
	if (tmp[3] == 0.0f)
		tmp[2] = (-b + sqrtf(tmp[3])) / (2 * a);
	else if (tmp[3] > 0.0f)
	{
		tmp[0] = (-b + sqrtf(tmp[3])) / (2 * a);
		tmp[1] = (-b - sqrtf(tmp[3])) / (2 * a);
		tmp[2] = (tmp[0] < tmp[1]) ^ flip ? tmp[0] : tmp[1];
		tmp[2] = (tmp[2] < 0.0f) ? tmp[1] : tmp[2];
	}
	if ((tmp[2] > 0.1f) && (tmp[2] < *t))
		*t = tmp[2];
	return (*t == tmp[2]);
}

int			find_closest_cone(t_env *obj, t_ray *ray, double *t)
{
	unsigned	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.cnc)
	{
		if (ray_intersect_cone(ray, &obj->scene.objs.cones[i],
			t, obj->draw_data.flip))
			rtn = i;
		i++;
	}
	return (rtn);
}

int			ray_intersect_plane(t_ray *ray, t_plane *p, double *t)
{
	t_vector	dist;
	double		norm;
	double		discr;
	double		answ;

	dist = vect_sub(&p->pos, &ray->start);
	norm = vect_dot(&p->rot, &dist);
	discr = vect_dot(&p->rot, &ray->dir);
	if ((answ = norm / discr) > 0.1f && (answ < *t))
		*t = answ;
	return (*t == answ);
}

int			find_closest_plane(t_env *obj, t_ray *ray, double *t)
{
	unsigned	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.pc)
	{
		if (ray_intersect_plane(ray,
			&obj->scene.objs.planes[i], t))
			rtn = i;
		i++;
	}
	return (rtn);
}
