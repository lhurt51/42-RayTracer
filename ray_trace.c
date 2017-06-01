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

void		check_norm(t_env *obj)
{
	if (vect_dot(&obj->draw_data.norm, &obj->draw_data.ray.dir) > 0.0f)
	{
		obj->draw_data.norm = vect_scale(-1.0f, &obj->draw_data.norm);
		obj->draw_data.flip = 1;
	}
	else
		obj->draw_data.flip = 0;
}

void		ray_tracing(t_env *obj, t_color *color)
{
	unsigned		level;
	double			t;

	level = 0;
	while ((obj->draw_data.coef > 0.0f) && (level < obj->scene.ray_depth))
	{
		t = 20000.0f;
		obj->draw_data.flip = 0;
		find_closest_obj(obj, &t);
		if (!hit_obj(obj, color, t))
			break;
		if (!obj->draw_data.flip)
		{
			handle_light(obj, color);
			apply_reflection(obj);
		}
		level++;
	}
}

int			set_draw_data(t_env *obj, unsigned x, unsigned y)
{
	t_vector		tmp;
	t_vector		ans;

	obj->draw_data.coef = 1.0;
	tmp = vect_create(x, y, obj->scene.fov * 10);
	obj->draw_data.ray.start = obj->scene.cam_pos;
	vec_mult_mat(&tmp, obj->draw_data.g_mat, &ans);
	obj->draw_data.ray.dir = vect_sub(&ans, &obj->draw_data.ray.start);
	if (!vect_norm(&obj->draw_data.ray.dir))
		return (0);
	return (1);
}

void		trace_each_pixel(t_env *obj)
{
	t_color			color;
	unsigned		x;
	unsigned		y;

	y = 0;
	while (y < obj->scene.w_height)
	{
		x = 0;
		while (x < obj->scene.w_width)
		{
			color = col_create(0, 0, 0);
			if (!set_draw_data(obj, x, y))
				return;
			ray_tracing(obj, &color);
			correct_gamma(&color);
			pixel_to_img(&obj->mlx, x++, y, color);
		}
		y++;
	}
}
