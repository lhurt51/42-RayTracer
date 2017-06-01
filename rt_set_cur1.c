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

int			set_cur_plane(t_env *obj)
{
	t_plane		cur;

	cur = obj->scene.objs.planes[obj->draw_data.cur_objs.cur_index];
	obj->draw_data.cur_objs.cur_mat = obj->scene.objs.materials[cur.mat];
	obj->draw_data.norm = cur.rot;
	if (vect_dot(&obj->draw_data.ray.dir, &cur.rot) > 0.0f)
	{
		obj->draw_data.norm = vect_scale(-1.0f, &obj->draw_data.norm);
		obj->draw_data.flip = 1;
	}
	else
		obj->draw_data.flip = 0;
	if (!vect_norm(&obj->draw_data.norm))
		return (0);
	return (1);
}

int			set_background(t_env *obj, t_color *color)
{
	t_color		test;

	test = col_create(0, 0, 0);
	test = col_mul_coef(&test, obj->draw_data.coef);
	*color = col_add(color, &test);
	return (0);
}
