/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACE_H
# define RAY_TRACE_H

# include "rtv1.h"
# include "mat.h"

/* Helper */
void		check_norm(t_env *obj);
/* Intersections */
int			find_closest_sphere(t_env *obj, t_ray *ray, double *t);
int			find_closest_cylinder(t_env *obj, t_ray *ray, double *t);
int			find_closest_cone(t_env *obj, t_ray *ray, double *t);
int			find_closest_plane(t_env *obj, t_ray *ray, double *t);
/* Lighting */
void		apply_reflection(t_env *obj);
void		correct_gamma(t_color *color);
void		handle_light(t_env *obj, t_color *color);
int			check_shadows(t_env *obj, t_ray *ray, double *t);
t_color		apply_specular(t_env *obj, t_ray light_ray, double light_proj,
	double view_proj);
void		apply_light(t_env *obj, t_ray *light_ray, t_color *color,
	double light_proj);
/* Set Current Obj */
int			set_cur_sphere(t_env *obj);
int			set_cur_cylinder(t_env *obj);
int			set_cur_cone(t_env *obj);
int			set_cur_plane(t_env *obj);
int			set_background(t_env *obj, t_color *color);
/* Find & Handle Closest Obj */
int			hit_obj(t_env *obj, t_color *color, double t);
void		find_closest_obj(t_env *obj, double *t);

#endif
