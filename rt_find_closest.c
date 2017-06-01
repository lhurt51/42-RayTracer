/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray_trace.h"

void		set_ray_start(t_env *obj, double *t)
{
	t_vector	scaled;

	scaled = vect_scale(*t, &obj->draw_data.ray.dir);
	obj->draw_data.ray.start = vect_add(&obj->draw_data.ray.start, &scaled);
}

int			hit_obj(t_env *obj, t_color *color, double t)
{
	set_ray_start(obj, &t);
	if (obj->draw_data.cur_objs.cur_obj == SPHERES)
	{
		if (!set_cur_sphere(obj))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_obj == CYLINDERS)
	{
		if (!set_cur_cylinder(obj))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_obj == CONES)
	{
		if (!set_cur_cone(obj))
			return (0);
	}
	else if (obj->draw_data.cur_objs.cur_obj == PLANES)
	{
		if (!set_cur_plane(obj))
			return (0);
	}
	else
		return (set_background(obj, color));
	return (1);
}

void		find_closest_obj(t_env *obj, double *t)
{
	int 	i;

	obj->draw_data.cur_objs.cur_index = -1;
	obj->draw_data.cur_objs.cur_obj = NONE;
	if ((i = find_closest_sphere(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = SPHERES;
	}
	if ((i = find_closest_cylinder(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = CYLINDERS;
	}
	if ((i = find_closest_cone(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = CONES;
	}
	if ((i = find_closest_plane(obj, &obj->draw_data.ray, t)) != -1)
	{
		obj->draw_data.cur_objs.cur_index = i;
		obj->draw_data.cur_objs.cur_obj = PLANES;
	}
}
