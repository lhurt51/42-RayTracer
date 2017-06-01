/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lighting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ray_trace.h"

t_color		apply_specular(t_env *obj, t_ray light_ray, double light_proj,
	double view_proj)
{
	t_vector	blinn_dir;
	t_color		rtn;
	double		tmp;
	double		blinn;

	rtn = col_create(0, 0, 0);
	blinn_dir = vect_sub(&light_ray.dir, &obj->draw_data.ray.dir);
	if ((tmp = vect_dot(&blinn_dir, &blinn_dir)) != 0.0f)
	{
		blinn = INVSQRTF(tmp) * MAX(light_proj - view_proj, 0.0f);
		blinn = obj->draw_data.coef * powf(blinn,
			obj->draw_data.cur_objs.cur_mat.power);
		rtn = col_mul_coef(&obj->draw_data.cur_objs.cur_mat.specular, blinn);
		rtn = col_mul(&rtn, &obj->draw_data.cur_objs.cur_light.intensity);
	}
	return (rtn);
}

void		apply_reflection(t_env *obj)
{
	t_vector	rtn;
	double		reflect;

	obj->draw_data.coef *= obj->draw_data.cur_objs.cur_mat.reflection;
	reflect = 2.0f * vect_dot(&obj->draw_data.ray.dir, &obj->draw_data.norm);
	rtn = vect_scale(reflect, &obj->draw_data.norm);
	obj->draw_data.ray.dir = vect_sub(&obj->draw_data.ray.dir, &rtn);
}

void		correct_gamma(t_color *color)
{
	double invgamma;

	invgamma = 0.45f;
	color->blue = powf(color->blue, invgamma);
	color->red = powf(color->red, invgamma);
	color->green = powf(color->green, invgamma);
}

void		apply_light(t_env *obj, t_ray *light_ray, t_color *color,
	double light_proj)
{
	t_color		tmp_color;
	double		lambert;

	lambert = vect_dot(&light_ray->dir, &obj->draw_data.norm)
		* obj->draw_data.coef;
	color->red += lambert * obj->draw_data.cur_objs.cur_light.intensity.red
		* obj->draw_data.cur_objs.cur_mat.diffuse.red;
	color->green += lambert * obj->draw_data.cur_objs.cur_light.intensity.green
		* obj->draw_data.cur_objs.cur_mat.diffuse.green;
	color->blue += lambert * obj->draw_data.cur_objs.cur_light.intensity.blue
		* obj->draw_data.cur_objs.cur_mat.diffuse.blue;
	tmp_color = apply_specular(obj, *light_ray, light_proj,
		vect_dot(&obj->draw_data.ray.dir, &obj->draw_data.norm));
	*color = col_add(color, &tmp_color);
}
