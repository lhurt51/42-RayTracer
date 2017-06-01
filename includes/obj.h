/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhurt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 17:36:13 by lhurt             #+#    #+#             */
/*   Updated: 2017/05/01 17:38:10 by lhurt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

enum	e_obj
{
	NONE,
	SETTINGS,
	MATERIALS,
	LIGHTS,
	SPHERES,
	CYLINDERS,
	CONES,
	PLANES
};

typedef struct	s_mat
{
	t_color		diffuse;
	t_color		specular;
	double		reflection;
	double		power;
}				t_mat;

typedef struct	s_light
{
	t_vector	pos;
	t_color		intensity;
}				t_light;

typedef struct	s_ray
{
	t_vector	start;
	t_vector	dir;
}				t_ray;

typedef struct	s_sphere
{
	t_vector	pos;
	double		radius;
	int			mat;
}				t_sphere;

typedef struct	s_cylinder
{
	t_vector	pos;
	t_vector	rot;
	double		radius;
	int			mat;
}				t_cylinder;

typedef struct	s_cone
{
	t_vector	pos;
	t_vector	rot;
	double		radius;
	int			mat;
}				t_cone;

typedef struct	s_plane
{
	t_vector	pos;
	t_vector	rot;
	int			mat;
}				t_plane;

#endif
