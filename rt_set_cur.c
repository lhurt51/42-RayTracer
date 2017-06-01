/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_set_cur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray_trace.h"

int			set_cur_sphere(t_env *obj)
{
	t_sphere	cur;

	cur = obj->scene.objs.spheres[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &cur.pos);
	check_norm(obj);
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_cur_cylinder(t_env *obj)
{
	t_cylinder	cur;
	t_vector	projection;

	cur = obj->scene.objs.cylinders[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &cur.pos);
	projection = vect_scale(vect_dot(&obj->draw_data.norm, &cur.rot), &cur.rot);
	obj->draw_data.norm = vect_sub(&obj->draw_data.norm, &projection);
	check_norm(obj);
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_cur_cone(t_env *obj)
{
	t_cone		cur;
	t_vector	projection;

	cur = obj->scene.objs.cones[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = vect_sub(&obj->draw_data.ray.start, &cur.pos);
	projection = vect_scale(vect_dot(&obj->draw_data.norm, &cur.rot), &cur.rot);
	obj->draw_data.norm = vect_sub(&obj->draw_data.norm, &projection);
	check_norm(obj);
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}
