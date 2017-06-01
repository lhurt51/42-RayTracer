/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray_trace.h"

int			ray_intersect_sphere(t_ray *ray, t_sphere *sphere, double *t)
{
	t_vector	dist;
	double		b;
	double		discr;
	double		ans;

	dist = vect_sub(&sphere->pos, &ray->start);
	b = vect_dot(&ray->dir, &dist);
	if ((discr = SQ(b) - vect_dot(&dist, &dist) + SQ(sphere->radius)) < 0.0f)
		return (0);
	ans = MIN((b - sqrtf(discr)), (b + sqrtf(discr)));
	if ((ans > 0.1f) && (ans < *t))
		*t = ans;
	return (*t == ans);
}

int			find_closest_sphere(t_env *obj, t_ray *ray, double *t)
{
	unsigned 	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.sc)
	{
		if (ray_intersect_sphere(ray,
			&obj->scene.objs.spheres[i], t))
			rtn = i;
		i++;
	}
	return (rtn);
}

int			ray_intersect_cylinder(t_ray *ray, t_cylinder *c, double *t, int flip)
{
	t_vector	dist;
	t_vector	cr;
	double		b;
	double		tmp[4];

	cr = vect_diff(&ray->dir, &c->rot);
	dist = vect_sub(&ray->start, &c->pos);
	dist = vect_diff(&dist, &c->rot);
	b = 2 * vect_dot(&cr, &dist);
	tmp[0] = SQ(b) - 4 * vect_dot(&cr, &cr)
		* (vect_dot(&dist, &dist) - SQ(c->radius));
	tmp[3] = (-b + sqrtf(tmp[0])) / (2 * vect_dot(&cr, &cr));
	if (tmp[0] > 0.0f)
	{
		tmp[1] = (-b - sqrtf(tmp[0])) / (2 * vect_dot(&cr, &cr));
		tmp[2] = (-b + sqrtf(tmp[0])) / (2 * vect_dot(&cr, &cr));
		tmp[3] = ((MIN(tmp[2], tmp[1]) < 0) ^ flip ? MAX(tmp[2], tmp[1])
			: MIN(tmp[2], tmp[1]));
	}
	if ((tmp[0] >= 0) && (tmp[3] > 0.1f) && (tmp[3] < *t))
		*t = tmp[3];
	return (*t == tmp[3]);
}

int			find_closest_cylinder(t_env *obj, t_ray *ray, double *t)
{
	unsigned 	i;
	int			rtn;

	i = 0;
	rtn = -1;
	while (i < obj->scene.obj_count.cyc)
	{
		if (ray_intersect_cylinder(ray,
			&obj->scene.objs.cylinders[i], t, obj->draw_data.flip))
			rtn = i;
		i++;
	}
	return (rtn);
}
