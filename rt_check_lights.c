/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_check_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray_trace.h"

int			check_shadows(t_env *obj, t_ray *ray, double *t)
{
	if (find_closest_sphere(obj, ray, t) != -1)
		return (1);
	else if (find_closest_cylinder(obj, ray, t) != -1)
		return (1);
	else if (find_closest_cone(obj, ray, t) != -1)
		return (1);
	else if (find_closest_plane(obj, ray, t) != -1)
		return (1);
	else
		return (0);
}

void		handle_light(t_env *obj, t_color *color)
{
	t_ray		light_ray;
	double		light_proj;
	double		t;
	unsigned	i;

	i = 0;
	light_ray.start = obj->draw_data.ray.start;
	while (i < obj->scene.obj_count.lc)
	{
		obj->draw_data.cur_objs.cur_light = obj->scene.objs.lights[i++];
		light_ray.dir = vect_sub(&obj->draw_data.cur_objs.cur_light.pos,
			&obj->draw_data.ray.start);
		if ((light_proj = vect_dot(&light_ray.dir, &obj->draw_data.norm))
			> 0.0f)
			if ((t = vect_norm(&light_ray.dir)))
			{
				light_proj *= INVSQRTF(t);
				if (!check_shadows(obj, &light_ray, &t) || !obj->scene.shadows)
					apply_light(obj, &light_ray, color, light_proj);
			}
	}
}
